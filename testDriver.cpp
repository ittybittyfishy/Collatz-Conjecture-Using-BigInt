// Olivia Fishbough
// Collatz Conjucture using BigInts. Using only two equations (3n + 1 and n / 2) tests to see if any number will eventually reach 1.

#include <iostream>
#include <limits.h>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

class BigInt
{
  private:
    vector<char> v;
  public:
    // default
    BigInt() { this->v.push_back(0);}
    // create object with an int parameter
    // Note: when 1234 is pushed to a big int is becomes 4321, so accessing the first elementis actually the last
    BigInt(int num)
    {
      char holder;
      while (num > 9)
        {
          holder = num % 10;
          num = num /10;
          this->v.push_back(holder);
        }
      holder = num;
      this->v.push_back(holder);
    }
    // create object from a string parameter
    BigInt(string str)
    {
     //copy(str.begin(), str.end(), v);
      for (int i = str.size() - 1; i >= 0; i--)
      {
        this->v.push_back(str[i] - '0');
      }
      if (this->v.empty()) 
      {
        this->v.push_back(0);
      }
    }

    BigInt operator+ (BigInt num)
    {
      int carry = 0;
      int ones = 0;
      BigInt temp;
      // now add each corresponding element together starting with last element
      // note: this actaully starts at the END of the vector, when 1234 is pushed to a big int is becomes 4321, so accessing the first element is actually the last
      for (int i = 0; i < max(this->v.size(), num.v.size()); i++)
        {
          int sum = 0;
          if ( i < this->v.size())
          {
            sum = sum + this->v[i];
          }
          if ( i < num.v.size())
          {
            sum = sum + num.v[i];
          }
          sum = sum + carry;
          carry = sum / 10; // carry over
          ones = sum % 10; // ones digit
          temp.v.push_back(ones);
        }
      if (carry != 0)
      {
        temp.v.push_back(carry);
      }
      temp.v.erase(temp.v.begin());
      return temp;
    }

    // * operator
    BigInt operator*(BigInt b)
    {
      BigInt result;
      result.v.resize(this->v.size() + b.v.size());
      int thisSize = this->v.size();
      int bSize = b.v.size();
      for (int i = 0; i < thisSize; i++)
        {
          int carry = 0;
          for(int j = 0; j < bSize; j++)
            {
              int prod = this->v[i] * b.v[j] + carry + result.v[i+j];
              carry = prod / 10;
              result.v[i + j] = prod % 10;
            }
          if (carry > 0)
          {
            result.v[bSize + i] = result.v[bSize + i] + carry;
          }
        }
      while(result.v.size() > 1 && result.v.back() == 0)
       {
          result.v.pop_back();
       }
      //result.v.erase(result.v.end() - 1);
      return result;
    }

    // PREFIX 
    BigInt operator++() 
      {
        BigInt one(1);
        return *this + one;
      }

    // POSTFIX
    BigInt operator++(int num) 
      {
        BigInt one(1);
        BigInt temp = *this;
        *this = *this + one;
        return temp;
      }

    // < operator
    bool operator<(BigInt num)
      {
        if (this->v.size() == num.v.size())
        {
          for (int i = this->v.size() - 1; i >= 0; i--)
            {
              if (this->v[i] < num.v[i])
              {
                return true;
              }
              else if (this->v[i] > num.v[i])
              {
                return false;
              }
              else {continue;}
            }
        }
        else if (this->v.size() < num.v.size())
        {
          return true;
        }
        return false;
      }

    // == operator
    bool operator ==(BigInt num)
    {
      if (this->v.size() == num.v.size())
      {
        for (int i = this->v.size() - 1; i >= 0; i--)
          {
            if (this->v[i] != num.v[i])
            {
              return false;
            }
            else {continue;}
          }
        return true;
      }
      return false;
    }

    bool isEven()
    {
      if (this->v[0] % 2 == 0)
      {
        return true;
      }
      else if (this->v[0] % 2 != 0)
      {
        return false;
      }
    }

    bool isOdd()
    {
      if (this->v[0] % 2 != 0)
      {
        return true;
      }
      else if (this->v[0] % 2 == 0)
      {
        return false;
      }
    }

    // half
    BigInt half()
      {
        BigInt result;
        bool remainder = false;
        for (int i = this->v.size() - 1; i >= 0; i--)
          {
            int holder = this->v[i];
            if (remainder == true)
            {
              holder += 10;
              remainder = false;
            }
            if (holder % 2 != 0)
            {
              remainder = true;
            }
            holder = holder / 2;
            result.v.push_back(holder);
          }
        reverse(result.v.begin(),result.v.end());
        while(result.v.size() > 1 && result.v.back() == 0)
       {
          result.v.pop_back();
       }
        return result;
      }

      
    friend ostream& operator<<(ostream& out, const BigInt& num)
      {
        if (num.v.size() < 9)
        {
          for (int i = num.v.size() - 1; i >= 0; i--)
            {
              cout << (int)num.v[i];
            }
          return out;
        }
        else
        {
          cout << (int)num.v[num.v.size() - 1] << ".";
          for (int i = 1; i <= 7; i++)
            {
              cout << (int)num.v[num.v.size() - 1 - i];
            }
          cout << "e" << num.v.size();
          return out;
          
        }
      }  
};



// create struct to store all details of 3n+1 sequences
struct ThreeNp1 
{
  BigInt start;
  BigInt steps;
  BigInt max;
  BigInt odd;
  BigInt even;
};
// utility function to see details of 3n+1 sequence
// notice that all values are BigInt... cout << BigInt
void print(ThreeNp1 temp)
  {
    cout << "start:"<<temp.start<<endl;
    cout << "steps:"<<temp.steps<<endl;
    cout << "max:"<<temp.max<<endl;
    cout << "odds:"<<temp.odd<<endl;
    cout << "evens:"<<temp.even<<endl;
}
// recursive function to find all details about 3n+1 sequence
// Function has a default parameter as the 3rd parameter
void findThreeNp1(BigInt n, ThreeNp1 & Np1, bool printSteps = false)
  {
    if (printSteps)
    {
      cout << "->"<<'('<< n <<')';
    }
    if (Np1.max < n) // BigInt::operator<( )
      Np1.max = n; // No need to overload - C++ provides operator=( )
    if (n == BigInt(1)) // BigInt::operator==( )
    {
      return; // we are done
    }
    else if (n.isEven()) // BigInt::isEven()
    {
      Np1.even++; // BigInt::operator++( )
      Np1.steps++;
      findThreeNp1(n.half(), Np1, printSteps); 
    }
    else if (n.isOdd()) // BigInt::isOdd( )
    {
      Np1.odd++;
      Np1.steps++;
      BigInt tempN(n); // BigInt constructor
      findThreeNp1(tempN*BigInt(3)+BigInt(1), Np1, printSteps); //BigInt::operator*( )
    }
    else
    {
      cout << "How the hell did I get here?\n";
      return;
    }
}

//https://en.wikipedia.org/wiki/Collatz_conjecture
int main()
{
  BigInt MAX(INT_MAX);
  cout << "The largest integer is "<< MAX<<endl;
  cout << "Twice the largest integer is "<< MAX + MAX << endl;
  BigInt start(INT_MAX); // BigInt constructor - use for submission
  //BigInt start(12); // BigInt constructor – use for testing
  bool printSteps = true;
  ThreeNp1 N = {start,0,0,0,0}; // initialize N
  findThreeNp1(start, N, printSteps); // print out the steps
  cout << endl;
  print(N);
}