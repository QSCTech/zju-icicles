package atm;

public class BankAccount {

    private double balance;

	//Constructors
	public BankAccount()
	{
		balance = 0;
	}
	
	public BankAccount(double initialBalance)
	{
		balance = initialBalance;
	}
	
	// Methods
	public void deposit(double amount)
	   {      
		balance = balance + amount;
	       
	    } 
	
	public boolean withdraw(double amount)    
	{ 
		if (balance>= amount)
			{
			balance = balance - amount;
			return true;
			}
		else
			return false;
        
    } 
	
	public double getBalance() 
	{ 
		return balance;
	}
}

