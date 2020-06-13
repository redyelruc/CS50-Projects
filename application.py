import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import date
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Query database for username
    cash = db.execute("SELECT cash FROM users WHERE id = :user",
                         user=session["user_id"])
    rows = db.execute("SELECT * FROM stocks WHERE user_id = :user",
                            user=session["user_id"])
    stocks =[]
    for row in rows:
        stock = lookup(row['stock_symbol'])
        current_value = stock['price'] * int(row['number_of_stocks'])
        stocks.append([row['stock_symbol'], stock['name'], round(stock['price'],2), row['number_of_stocks'], round(current_value, 2)])
    return render_template("index.html", cash = round(cash[0]['cash'],2), stocks=stocks)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html", stock = "")
    else:
        stock = lookup(request.form.get("stock_symbol").upper())
        if stock == None:
            return apology("cannot find stock", 403)
        else:
            cash_left = db.execute("SELECT cash FROM users WHERE id = :user", user=session["user_id"])[0]['cash']
            number_of_stocks = int(request.form.get("number_of_stocks"))
            cost_of_stocks = round(stock['price'] * number_of_stocks,2)
            # check there are enough funds
            if cost_of_stocks > cash_left:
                flash("Not enough funds in your account for this transaction.")
                return redirect("/buy")
            else:

                # check if user already owns some of this stock
                stocks = db.execute("SELECT number_of_stocks from stocks WHERE stock_symbol = :stock_sym AND user_id = :user",
                            stock_sym= stock["symbol"], user=session["user_id"])
                if not stocks:
                    # insert new row into stocks table
                     db.execute("INSERT INTO stocks(user_id, stock_symbol, number_of_stocks) VALUES (:user, :stock, :number)",
                                user=session["user_id"], stock=stock['symbol'], number=number_of_stocks)
                else:
                    new_total_stocks = number_of_stocks + stocks[0]['number_of_stocks']
                    # update amount of stocks held
                    db.execute("UPDATE stocks SET number_of_stocks = :number WHERE stock_symbol = :stock AND user_id = :user",
                          number=new_total_stocks, stock=stock['symbol'], user=session["user_id"])
                # insert row into history table
                db.execute("INSERT INTO history(user_id, stock_symbol, number_of_stocks, total_value, transaction_type, date) VALUES (:user, :stock, :number, :total, :trans, :date)",
                            user=session["user_id"], stock = stock['symbol'], number=number_of_stocks, total=cost_of_stocks, trans="BUY", date = date.today())
                
                cash_left = cash_left - cost_of_stocks
                # update cash in user's table
                db.execute("UPDATE users SET cash = :cash_left WHERE id = :user",
                            cash_left=cash_left, user=session["user_id"])
                flash("Bought!")
                return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # get history
    rows = db.execute("SELECT * FROM history WHERE user_id = :user",
                            user=session["user_id"])
    history =[]
    for row in rows:
        history.append([row['user_id'],row['stock_symbol'], row['number_of_stocks'], 
                        row['total_value'], row['transaction_type'], row['date']])
    
    # redirect user to index page
    return render_template("history.html", history=history)



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")

@app.route("/cash", methods=["GET", "POST"])
@login_required
def add_cash():
    if request.method == "GET":
        # Display form for user to enter stock to search
        return render_template("cash.html", stock = "")
    else:
        more_cash = int(request.form.get("more_cash"))
        if more_cash == None:
            return apology("you must enter an amount to add", 403)
        else:
            cash = db.execute("SELECT cash FROM users WHERE id = :user",
                         user=session["user_id"])[0]['cash']
            new_cash = cash + more_cash
            db.execute("UPDATE users SET cash = :cash WHERE id = :user",
                          cash = new_cash, user=session["user_id"])
            flash('Cash Added')
            return redirect('/')
            
@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        # Display form for user to enter stock to search
        return render_template("quote.html", stock = "")
    else:
        stock = lookup(request.form.get("stock_symbol"))
        if stock == None:
            return apology("cannot find stock", 403)
        else:
            return render_template("quote.html", stock = stock)



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        # Display form for user to create account
        return render_template("register.html")
    else:
        # register the new user
        # check username is not blank
        if not request.form.get("username"):
            return apology("must provide username", 403)
        # check password id not blank
        if not request.form.get("password"):
            return apology('must provide password', 403)
        # check username is unique
        if db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username")):
            return apology("username already taken", 403)
        # check password and confirmation are same
        if request.form.get("password") != request.form.get("confirm-password"):
            return apology("password and confirmation do not match", 403)
        # hash the password and create row in db
        db.execute("INSERT INTO users(username, hash) VALUES (:username, :hash)",
            username=request.form.get("username"), hash=generate_password_hash(request.form.get("password")))

        # make sure that the new user is logged in
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # set the session so we know who is logged in
        session["user_id"] = rows[0]["id"]
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    cash = db.execute("SELECT cash FROM users WHERE id = :user",
                         user=session["user_id"])
    rows = db.execute("SELECT * FROM stocks WHERE user_id = :user",
                            user=session["user_id"])
    stocks =[]
    for row in rows:
        stock = lookup(row['stock_symbol'])
        current_value = stock['price'] * int(row['number_of_stocks'])
        stocks.append([row['stock_symbol'], stock['name'], round(stock['price'],2), row['number_of_stocks'], round(current_value, 2)])

    
    if request.method == "GET":
        return render_template("sell.html", cash = round(cash[0]['cash'],2), stocks=stocks)
    else:
        stock_sym = request.form.get("stk_sym").upper()
        number_to_sell = int(request.form.get("number_to_sell"))
        stocks_in_portfolio = db.execute("SELECT number_of_stocks from stocks WHERE user_id = :user AND stock_symbol = :symbol",
                                        user = session["user_id"], symbol = stock_sym)
        if not stocks_in_portfolio:
            return apology('cannot find this stock in your portfolio')
        else:
            stocks_in_portfolio = stocks_in_portfolio[0]
        
        num_stocks_in_portfolio = int(stocks_in_portfolio['number_of_stocks'])
        if num_stocks_in_portfolio < number_to_sell:
            return apology("you cannot sell more than you own")
        else:
            current_listing = lookup(stock_sym)
            current_price = current_listing['price']
            money_made = current_price * number_to_sell
            num_stocks_in_portfolio -= number_to_sell
            current_cash = db.execute("SELECT cash FROM users WHERE id = :user", user=session["user_id"])[0]['cash']
            new_total_cash = current_cash + money_made
            if num_stocks_in_portfolio == 0:
                db.execute("DELETE FROM stocks WHERE stock_symbol = :stock AND user_id = :user",
                          stock=current_listing['symbol'], user=session["user_id"])
            else:
                # update number of stocks held
                db.execute("UPDATE stocks SET number_of_stocks = :number WHERE stock_symbol = :stock AND user_id = :user",
                          number=num_stocks_in_portfolio, stock=current_listing['symbol'], user=session["user_id"])
           
            # update amount of cash left
            db.execute("UPDATE users SET cash = :cash WHERE id = :user",
                          cash=new_total_cash, user=session["user_id"])            
            # insert row into history table
            db.execute("INSERT INTO history(user_id, stock_symbol, number_of_stocks, total_value, transaction_type, date) VALUES (:user, :stock, :number, :total, :trans, :date)",
                            user=session["user_id"], stock = current_listing['symbol'], number=number_to_sell, total=money_made, trans="SELL", date = date.today())
            
            flash("Sold!")
            return redirect("/")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
