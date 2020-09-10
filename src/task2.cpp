#include<iostream>
#include<fstream>
#include<cmath> 
#include<vector>
#include<tuple>

using namespace std;

vector<uint> ReadArray(char *filename)
{
	ifstream data_file(filename);
	vector<uint> data;
	uint value;
	while (data_file >> value)
	{
		data.push_back(value);
	}
	return data;
}

void Print(const vector<uint>& data)
{
	for(const auto &i: data)
	{
		cout << i << ' ';
	}
	cout << endl;
}

tuple<uint, uint> FindMissingValues(const vector<uint>& data)
{
	uint n = data.size() + 1;
	ulong s1 = n*(n+1)/2, s2 = s1*(2*n+1)/3; // n*(n+1)*(2n+1)/6;
	
	for(const auto &i: data)
	{
		s1 -= i;
		s2 -= i*i;
	}
	
	ulong d = static_cast<ulong>(sqrt(2*s2 - s1*s1));
	ulong a = static_cast<uint>((s1 - d)/2);
	ulong b = static_cast<uint>((s1 + d)/2);
	return make_tuple(a, b);
}

tuple<uint, uint> FindMissingValuesWithXor(const vector<uint>& data)
{
	uint n = data.size() + 1, x = n^(n-1);
	
	for(vector<uint>::size_type i = 0; i < data.size(); ++i)
	{
		x = x^data[i]^i;
	}
	// x = a^b, where a and b - missing values
	x = x&(~(x-1)); 
	// x contains 1 in least significant bit,
	// in which a and b is distinguished
	
	// split all values into two sets according to the value of this bit
	// a and b will be in different sets
	
	uint a = 0, b = 0;
	for(vector<uint>::size_type i = 0; i < data.size(); ++i)
	{
		if((data[i] & x) == 0)
		{
			a ^= data[i];
		}
		else
		{
			b ^= data[i];
		}
	}
	for(uint i = 0; i <= n; ++i)
	{
		if((i & x) == 0)
		{
			a ^= i;
		}
		else
		{
			b ^= i;
		}
	}
	// after that a and b will will contain the missing values
	
	return make_tuple(a, b);
}

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		cout << "Usage: " << argv[0] << " <data_file> [-xor]" << endl;
		return 0;
	}
	
	vector<uint> data = ReadArray(argv[1]);
	
	cout << "Input data:" << endl;
	Print(data);
	tuple<uint, uint> missing_values;
	if(argc < 3)
	{
		missing_values = FindMissingValues(data);
	}
	else
	{
		cout << "Using xor algorithm" << endl;
		missing_values = FindMissingValuesWithXor(data);
	}
	cout << "Missing values: ";
	cout << get<0>(missing_values) << ", ";
	cout << get<1>(missing_values) << endl;
	
	return 0;
}
