//                      Name-  Sanjana Goel


#include<iostream>
#include<stack>
#include<queue>
using namespace std;
stack<string>s;  // for maintaining original order
queue<string>q; // lane
queue<string>wq; // waiting queue
int countarr[10]={0,0,0,0,0,0,0,0,0,0};
class CarParkingSystem
{
	private: string licenseNo;
	public:
	CarParkingSystem(string ln)
	{
		licenseNo=ln;
	}
	
	void arrival(string ln)
	{
		int lanesize=q.size();
		if(lanesize<=10)
		{
			q.push(ln);
		cout<<"Car with license plate no: "<<ln<<" is parked successfully!"<<endl;
		}
		else
		{
		   wq.push(ln);	
	    cout<<"Sorry! there is no room for this car in the garage. Please wait"<<endl;	
	    }
	
	}
	
	void reorderLane()
	{
		// reversing stack to preserve the lane order
			while(!s.empty())    //stack to queue
			{
				q.push(s.top());
		 		s.pop();
			}
			while(!q.empty())   //queue to stack
			{
				s.push(q.front());
		 		q.pop();
			}
			while(!s.empty())    //stack to queue
			{
				q.push(s.top());
		 		s.pop();
			}
	}
	
	void reorderWaitingQueue()
	{
		// reversing stack to preserve the Waiting Queue order
			while(!s.empty())    //stack to queue
			{
				wq.push(s.top());
		 		s.pop();
			}
			while(!wq.empty())   //queue to stack
			{
				s.push(wq.front());
		 		wq.pop();
			}
			while(!s.empty())    //stack to queue
			{
				wq.push(s.top());
		 		s.pop();
			}
	}
	
	void departure(string ln)
	{
		if(ln==q.front()) // if the car is northern most
		{
			q.pop();
		cout<<"the number of times the car was moved within the garage : "<<countarr[0]+1<<endl;
		cout<<"Car with license plate no: "<<ln<<" is departure successfully!"<<endl;
		parkFromwaitingQueue();
		}
		else
		{
			int i=0;
		 	while(!q.empty()&& q.front()!=ln) //all cars to the north of the car are moved out
		 	{
		 		s.push(q.front());
		 		q.pop();
		 		countarr[i]=countarr[i]+1;
		 		i++;
			}
			if(q.empty())           //if not found in lane 
			{
				reorderLane();
				waitingQueue(ln); // departure the car from waiting queue
			}
			else
			{
				q.pop();            // departure that car
			cout<<"the number of times the car was moved within the garage : "<<countarr[i]+1<<endl;
			cout<<"Car with license plate no: "<<ln<<" is departure successfully!"<<endl;		
			    while(!q.empty())
			    {
				    s.push(q.front());
		 		    q.pop();
			    }
			    reorderLane();
			}
			//park  From waiting Queue because one slot becomes free
			parkFromwaitingQueue();
		}
	}
	
	void parkFromwaitingQueue()
	{
		string lno;
		if(!wq.empty())
		{
		  lno=wq.front();
		  cout<<"Room is free now to park your car"<<endl;
		  arrival(lno);
		  wq.pop();
		}
	}
	
	void waitingQueue(string ln)
	{
		if(ln==wq.front()) // if the car is northern most in waiting queue
		{
			wq.pop();
		cout<<"the number of times the car was moved within the garage : 0"<<endl;	
		cout<<"Car with license plate no: "<<ln<<" is departure successfully from the waiting queue!"<<endl;	
		}
		else
		{
		  while(!wq.empty()&& wq.front()!=ln) //all cars to the north of the car are moved out
		  {
		 	s.push(wq.front());
		 	wq.pop();
		  }	
		  if(wq.empty())           //if not found in lane 
		  {
			reorderWaitingQueue();
			cout<<"Invalid car license plate no ! OOps Record not found"<<endl;
		  }
		  else
		  {
				wq.pop();            // departure that car
		cout<<"the number of times the car was moved within the garage : 0"<<endl;	
		cout<<"Car with license plate no: "<<ln<<" is departure successfully from the waiting queue!"<<endl;	
			    while(!wq.empty())
			    {
				    s.push(wq.front());
		 		    wq.pop();
			    }
			    reorderWaitingQueue();
		  }
		}
	}	
};

int main()
{
	cout<<"          Welcome to the car parking system         "<<endl;
	cout<<"Enter 'A' for arrival or 'D' for departure and license plate no. for ex- A licenseNo"<<endl;
	cout<<"Enter quit to stop"<<endl;
	string input,lno;
	int size;
    while(true)
	{
      getline(cin,input);
      if(input=="quit")
         break;
      size=input.length();
      lno = input.substr(2,size-2);
      CarParkingSystem ps(lno);
      if(input[0]=='A')
      {
      	ps.arrival(lno);
	  }
      else
      {
      	ps.departure(lno);
	  }   
    }
	return 0;
}
