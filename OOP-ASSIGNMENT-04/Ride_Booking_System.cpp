#include<iostream>
using namespace std;

int Length(const char* str)
{
	int i = 0;
	while (str[i] != '\0')
		i++;

	return i;
}


void CopyStr(const char* src, char*& des)
{
	des = new char[Length(src) + 1];

	int i = 0;
	while (src[i] != '\0')
	{
		des[i] = src[i];
		i++;
	}

	des[i] = '\0';
}


class Ride 
{
protected:
	char* riderName;
	double distance;
public:
	Ride(const char* name, double dist):distance(dist)
	{
		riderName = nullptr;
		CopyStr(name, riderName);
	}
	virtual double calculateFare() = 0;
	virtual void applySurgePricing() = 0;
	virtual void validateRide() = 0;
	virtual void displayRideDetails() = 0;
	virtual ~Ride() {}
};
class EconomyRide : public Ride
{
public:
	EconomyRide(const char* name, double dist) :Ride(name, dist) {}

	double calculateFare() override
	{
		return (50 + (distance * 20));
	}
	void applySurgePricing() override
	{
		cout << "With Surge: " << calculateFare() * 1.10;
	}
	void validateRide() override
	{
		
			if (distance <= 0)
				throw("Distance is invalid...");
	}
	void displayRideDetails() override
	{
		cout << "Economic Ride----" << endl;

		cout << "RiderName: " << riderName << endl;
		cout << "Distance: " << distance << endl;
		cout << "Actual Fare: " << calculateFare() << endl;
	}
};
class PremiumRide : public Ride 
{
private:
	double luxuryFee;
public:
	PremiumRide(const char* name, double dist, double fee) :luxuryFee(fee), Ride(name, dist) {}
	double calculateFare() override
	{
		return (100 + (distance * 40) + luxuryFee);
	}
	void applySurgePricing() override
	{
		
			cout << "With Surge: " << calculateFare() * 1.25;
	}
	void validateRide() override
	{
		if (luxuryFee < 0)
			throw("LuxuryFee is invalid...");
	}
	void displayRideDetails() override
	{
		cout << "Premium Ride----" << endl;

		cout << "RiderName: " << riderName << endl;
		cout << "Distance: " << distance << endl;
		cout << "Luxury Fee: " << luxuryFee << endl;

		cout << "Actual Fare: " << calculateFare() << endl;
	}
};
class BikeRide : public Ride
{
public:
	BikeRide(const char* name, double dist) : Ride(name, dist) {}
	double calculateFare() override
	{
			return (distance * 10);
		
	}
	void applySurgePricing() override
	{
		cout << "No Surge allowed";
	}
	void validateRide() override
	{
		if (distance > 50)
			throw("Distance is greater than 50...");
	}
	void displayRideDetails() override
	{
		cout << "Bike Ride----" << endl;

		cout << "RiderName: " << riderName << endl;
		cout << "Distance: " << distance << endl;
		cout << "Actual Fare: " << calculateFare() << endl;
	}
};

class SharedRide : public Ride
{
private:
	int passengers;
public:
	SharedRide(const char* name, double dist, int p) :Ride(name, dist), passengers(p) {}
	double calculateFare() override
	{
			return (distance * 25);
		
	}
	void applySurgePricing() override
	{

		cout << "Fair Split for " << passengers << " Passengers : " << calculateFare() / passengers;
		
	}
	void validateRide() override
	{
		if (passengers <1)
			throw("Passenger Number is invalid...");
	}
	void displayRideDetails() override
	{
		cout << "Shared Ride----" << endl;

		cout << "RiderName: " << riderName << endl;
		cout << "Distance: " << distance << endl;
		cout << "Passengers: " << passengers << endl;

		cout << "Actual Fare: " << calculateFare()<<endl;

	}

};

class RideManager
{
private:
	Ride** rides;
	int count;
public:
	RideManager()
	{
		count = 0;
		rides = NULL;
	}
	~RideManager()
	{
		for (int i = 0;i < count;i++)
			delete  rides[i];
		delete[] rides;
	}
	void addRide(Ride* r)
	{
		Ride** rr;
		rr = NULL;
		rr = new Ride * [count+1];
		for (int i = 0;i < count;i++)
		{
			rr[i] = rides[i];
		
		}
		rr[count] = r;
		count++;
		delete[] rides;

		rides = rr;

		
	}
	void processRides()
	{
		for (int i = 0;i < count;i++)
		{
			try {
				cout << endl;
				rides[i]->validateRide();

				rides[i]->displayRideDetails();

				cout << "Final Fair: "<<endl;
				rides[i]->applySurgePricing();

				cout << endl;
			}

			catch (const char* msg)
			{
				cout << endl;
				cout << "Error: " << msg;
				cout << endl;
			}
		}
	}
	void displayAllRides()
	{
		for (int i = 0;i < count;i++)
		{
			rides[i]->displayRideDetails();
			cout << endl;
		}
	}

};

int main() {
	// Step 1: Create Ride Objects (Independently)
	Ride* r1 = new EconomyRide("Ali", 5);
	Ride* r2 = new PremiumRide("Sara", 10, 200);
	Ride* r3 = new BikeRide("Ahmed", 60); // invalid case
	Ride* r4 = new SharedRide("Zain", 20, 4);
	Ride* r5 = new SharedRide("Hassan", 15, 0); // invalid case
	// Step 2: Create Ride Manager
	RideManager manager;
	// Step 3: Add Rides to Manager
	manager.addRide(r1);
	manager.addRide(r2);
	manager.addRide(r3);
	manager.addRide(r4);
	manager.addRide(r5);
	// Step 4: Process All Rides
	cout << "Processing All Rides...\n\n";
	manager.processRides();

	return 0;
}