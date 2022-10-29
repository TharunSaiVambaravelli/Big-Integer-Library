#include<iostream>
#include<string>
using namespace std;
class BigInteger
{
    string number;
    public:
    BigInteger()
    {
        number="";
    }
     BigInteger(string num)
    {
        setNumber(num);
    }
    BigInteger operator +(BigInteger n2)
    {
        BigInteger *sum;
        sum->setNumber(add((*this).getNumber(),n2.getNumber()));
	    return *sum;
    }
     BigInteger& operator -(BigInteger n2)
    {
        BigInteger *difference;
        difference->setNumber(subtract((*this).getNumber(),n2.getNumber()));
	    return *difference;
    }
    BigInteger& operator *(BigInteger n2)
    {
        BigInteger *product=new BigInteger;
        product->setNumber( multiply((*this).getNumber(),n2.getNumber()) );
	    return *product;
    }
    BigInteger& operator %(BigInteger n2)
    {
        BigInteger *quotient=new BigInteger;
        quotient->setNumber(modulus((*this).getNumber(),n2.getNumber()) );
	    return *quotient;
    }
     void setNumber(string s)
    {
        int i=0;
        while(i+1<s.length()&&s[i]=='0')
        {
            i++;
        }
        s.erase(0,i);
    	number = s;
    }
    const string& getNumber()
    {
        return number;
    }
    bool greater(string n1,string n2)
    {
        if(n1.length() > n2.length())
			return true;
		if(n1.length() < n2.length() )
			return false;
		return n1>n2;
    }
    bool lesser(string n1,string n2)
    {
        if(n1.length() < n2.length())
			return true;
		if(n1.length() > n2.length() )
			return false;
		return n1<n2;
    }
    bool equals(string n1,string n2)
    {
        return !(greater(n1,n2))&&!(lesser(n1,n2));
    }
    string add(string n1,string n2)
    {
        string result;
        if(n1.length()<n2.length())
        {
            std::swap(n1,n2);
        }
        int carry=0,temp=0,i=n1.length()-1;
        for(int j=n2.length()-1;j>=0;j--)
        {
            temp=(n1[i]-'0')+(n2[j]-'0')+carry;
            carry=temp/10;
            temp=temp%10;
            result=(char)(temp+'0')+result;
            i--;
        }
        while(i>-1)
        {
            temp=n1[i]-'0'+carry;
            carry=temp/10;
            temp=temp%10;
            result=(char)(temp+'0')+result;
            i--;
        }
        if(carry==1)
        {
            result='1'+result;
        }
        return result;
    }
    string subtract(string n1,string n2)
    {
        string result;
        int borrow=0,temp=0,j=n2.length()-1,i;
        for(i=n1.length()-1;i>=0&&j>=0;i--)
        {
            temp=n1[i]-n2[j]-borrow;
            if(temp<0)
            {
                temp+=10;
                borrow=1;
            }
            else{
                borrow=0;
            }
            result=(char)(temp+'0')+result;
            j--;
        }
        while(i>-1)
        {
            temp=n1[i]-'0'-borrow;
            if(temp<0)
            {
                temp+=10;
                borrow=1;
            }
            else{
                borrow=0;
            }
            result=(char)(temp+'0')+result;
            i--;
        }
        int k=0;
        while(k+1<result.length()&&result[k]=='0')
        {
            k++;
        }
        result.erase(0,k);
    	number = result;
        return result;
    }
    string multiply(string n1, string n2)
    {
	    if(n1.length() > n2.length()) 
		    std::swap(n1,n2);

	    string res= "0";
	    for(int i=n1.length()-1; i>=0; --i)
	    {
		string temp = n2;
		int currentDigit = n1[i]-'0';
		int carry = 0;

		for(int j=temp.length()-1; j>=0; --j)
		{
			temp[j] = ((temp[j]-'0') * currentDigit) + carry;

			if(temp[j] > 9)
			{
				carry = (temp[j]/10);
				temp[j] -= (carry*10);
			}
			else
				carry = 0;

			temp[j] += '0'; 
		}
		if(carry > 0)
			temp.insert(0, 1, (carry+'0'));
		
		temp.append((n1.length()-i-1), '0'); 
		res = add(res, temp); 
	    }
	    while(res[0] == '0' && res.length()!=1) 
		    res.erase(0,1);
	    return res;
    }
    string exponentiation(string n,long long int e)
    {
        if(e==1||n=="0"||n=="1") return n;
        if(e==0) return "1";
        string result=exponentiation(n,e/2);
        result=multiply(result,result);
        if(e%2==1)
        {
            result=multiply(result,n);
        }
        return result;
    }
    string factorial(string n)
    {
        if(equals(n,"0")||equals(n,"1"))
            return n;
        return multiply(n,factorial(subtract(n,"1")));
    }
    
    
    string modulus(string n,string divisor)
    {
        if(lesser(n,divisor)) return n;
        if(!(greater(n,divisor))&&!(lesser(n,divisor))) return "0";
        if(!(greater("1",divisor))&&!(lesser("1",divisor))) return "0";
        if(equals(divisor,"0")) return "0";
        string pdividend=n.substr(0,divisor.length()),pdivisor=divisor;
        int temp=0;
        for(int i=0;i<=n.length()-divisor.length();i++)
        {
            temp=0;
            pdivisor=divisor;
            while(greater(pdividend,pdivisor))
            {
                pdivisor=add(pdivisor,divisor);
                temp++;
            }
               if(pdividend==pdivisor)
               {
                   if(i==n.length()-divisor.length())
                        return "0";
                   pdividend=n[divisor.length()+i];
        
               }
               else
               {
                   if(temp==0)
                   {
                     if(i!=n.length()-divisor.length())
                        pdividend+=n[divisor.length()+i];
                     continue;
                   }
                    pdividend=subtract(divisor,subtract(pdivisor,pdividend));
                    if(i!=n.length()-divisor.length())
                        pdividend+=n[divisor.length()+i];
                    
               }
        }
        return pdividend;
    }
    
 
  
   
 void gcd(string num1,string num2){
    if(equals(num1,"0"))
    {
        cout<<num2;
        return;
    }
    if(equals(num2,"0"))
    {
        cout<<num1;
        return;
    }
    if(equals(num1,num2))
    {
         cout<<num1;
         return;
    }
     string rem,temp;
    if(lesser(num1,num2))
    {
        rem=num1;
        num1=num2;
        num2=rem;
    }
    while(greater(num2,"0"))
    {
        rem=modulus(num1,num2);
        temp=num2;
        num2=rem;
        num1=temp;
    }
    
    cout<<num1;
   }
  
   
};
class Node{
    public:
    string str;
    Node* next;
    Node(string s)
    {
        str=s;
        next=NULL;
    }
};
class Nodeoptr{
    public:
    char ch;
    Nodeoptr* next;
    Nodeoptr(char c)
    {
        ch=c;
        next=NULL;
    }
};
bool isdigit(char c)
{
    if(c>='0'&&c<='9')
        return true;
    else 
        return false;
}
bool isoperator(char c)
{
    if(c=='x'||c=='+'||c=='-'||c=='X')
        return true;
    else
        return false;
}
int precedence(char op){
    if(op == 'x'||op =='X')
    return 2;
    
    if(op == '+'||op == '-')
    return 1;
    
    
        return 0;
}
 
string performop(string a, string b, char op){
    BigInteger n1(a),n2(b);
    if(op=='+')
    {
        return  n1.add(n1.getNumber(),n2.getNumber());
    }
    else if(op=='-')
    {
        return n1.subtract(n1.getNumber(),n2.getNumber());
    }
    else if(op=='x'||op =='X')
    {
         return n1.multiply(n1.getNumber(),n2.getNumber());
    }
    else{
        return "";
    }
}
string calculator(string str){

     
    Node *operand=NULL;
    Nodeoptr *optr=NULL;
     
    int i;
    for(i = 0; i < str.length(); i++){
         
        if(isdigit(str[i])){
            string temp="";
            while(i < str.length() && isdigit(str[i]))
            {
                temp+=str[i];
                i++;
            }
            Node *node=new Node(temp); 
            if(operand==NULL)
            {
                operand=node;
            }
            else
            {
               node->next=operand;
               operand=node;
            }
            i--;
        }
        else
        {
            
            while(optr!=NULL && precedence(optr->ch)>=precedence(str[i]) )
            {
                string temp2 = operand->str;
                operand=operand->next;
                string temp1 = operand->str;
                operand=operand->next;
                char opr=optr->ch;
                optr=optr->next;
                string result=performop(temp1,temp2,opr);
                Node *node=new Node(result); 
                if(operand==NULL)
                {
                    operand=node;
                }
                else
                {
                node->next=operand;
                operand=node;
                }
            
            }
            
            Nodeoptr *node=new Nodeoptr(str[i]);
            if(optr==NULL)
            {
                optr=node;
            }
            else
            {
               node->next=optr;
               optr=node;
            }
            
        }
    }
     
    while(optr!=NULL){
        string temp2 = operand->str;
        operand=operand->next;
        string temp1 = operand->str;
        operand=operand->next;
        char opr=optr->ch;
        optr=optr->next;
        string result=performop(temp1,temp2,opr);
        Node *node=new Node(result); 
        if(operand==NULL)
        {
            operand=node;
        }
        else
        {
            node->next=operand;
            operand=node;
        }
            
    }
    string *res=new string(operand->str);
    return *res;
}
int main()
{
    int ch=0;
    cin>>ch;
    if(ch==4)
    {
        string str;
        cin>>str;
        cout<<calculator(str);
    }
    else if(ch==1)
    {
        string str;
        long long int e;
        cin>>str;
        cin>>e;
        BigInteger n(str);
        cout<<n.exponentiation(n.getNumber(),e);
    }
    else if(ch==2)
    {
        string str1,str2;
        cin>>str1;
        cin>>str2;
        BigInteger n1(str1),n2(str2);
        n1.gcd(n1.getNumber(),n2.getNumber());
    }
    else if(ch==3)
    {
        string str;
        cin>>str;
        BigInteger n(str);
        cout<<n.factorial(n.getNumber());
    }
    else{
    }
    return 0;
}



