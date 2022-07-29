#include <iostream>
#include <vector>
void LogError(std::string Msg) {

	std::cout << Msg << "\n";

}

unsigned int BinaryToGrayCode(unsigned int Binary) {

	return ((Binary >> 1) ^ Binary);

}

class CanonicalForm {

	unsigned int _getNumberOfInputs(std::string InputExpression) {

		char operators[4] = { '.', '+', '!', ' '};

		unsigned int count = 0;

		unsigned int Size = InputExpression.size();

		bool Found = false;

		for (unsigned int Index = 0; Index < Size; Index++) {
			
			for (unsigned int i = 0; i < 4; i++) {

				Found = false;

			}

		}
		return 0;

	}

	bool _setInputs(unsigned char* Inputs) {

		return true; 

	}

public:
	unsigned int NumberOfInputs = 0;
	unsigned char* Inputs = nullptr;
	/// <summary>
	/// Just Providing Some Structure To The Input Of Canonical Form
	/// </summary>
	/// <param name="InputExpression">Always Pass A String</param>
	CanonicalForm(const char* InputExpression=nullptr) {

		if (InputExpression == nullptr) {

			LogError("Nothing Passed");
			::exit(-1);

		}

		*this = CanonicalForm(std::string(InputExpression));

	}
	CanonicalForm(std::string InputExpression = "") {

		if (InputExpression == "") {

			LogError("Nothing Passed");
			::exit(-1);

		}

		NumberOfInputs = _getNumberOfInputs(InputExpression);

		Inputs = new unsigned char[NumberOfInputs];

		_setInputs(Inputs);

	}

};

class SOP_INPUT {

public:

	std::vector<unsigned int> vArray;
	unsigned int BitsRequired = 0;
	
	/// <summary>
	/// Can Be Optimized
	/// Debug Mode Time Taken for 0 - 65536 => 203ms
	/// Release Mode Time Taken for 0 - 65536 => 14ms
	/// </summary>
	/// <param name="">Send Unsigned Integer As Input But It Only Takes Into Account 31 Bits</param>
	/// <returns></returns>
	static std::string convertIntoBinaryString(unsigned int Number) {

		std::string Output = "";

		for (unsigned int i = 1; i < 31; i++) {

			((Number >> (30 - i)) & 1) ? Output += '1' : Output += '0';

		}

		unsigned int Index = 0;

		//Minimize
		while (Output[Index] == '0' && !(Index > Output.size())) {

			Index++;

		}

		std::string Temp = "";

		for (unsigned int i = Index; i < Output.size(); i++) {

			Temp += Output[i];

		}

		Output = Temp;

		if (Output.size() == 0) {

			Output = "0";

		}

		return Output;

	}

	static bool isANumber(char Character) {

		if (Character >= '0' && Character <= '9') {

			return true;

		}

		return false;

	}

	//Checks Are Not Perfomed
	static unsigned int convertIntoNumber(std::string Characters) {

		unsigned int Size = Characters.size();

		if (Size > 9) {

			return UINT32_MAX;

		}

		unsigned int Number = 0;

		for (unsigned int Index = 0; Index < Size; Index++) {

			Number += static_cast<unsigned int>(pow(10, (Size - Index - 1))) * (Characters[Index] - '0');

		}

		return Number;

	}

	unsigned int GetLargestInteger(std::vector<unsigned int> Input) {

		unsigned int LargestNumber = 0;

		for (unsigned int Index = 0; Index < Input.size(); Index++) {

			if (Input[Index] > LargestNumber) {

				LargestNumber = Input[Index];

			}

		}

		return LargestNumber;

	}

	std::vector<unsigned int>GetNumberArray(std::string Expression, unsigned int& BitsRequired) {

		std::vector<unsigned int>Output;

		std::vector<std::string>StringArray;

		std::string Temporary = "";

		for (unsigned int Index = 0; Index < Expression.size(); Index++) {

			if (SOP_INPUT::isANumber(Expression[Index])) {

				Temporary += Expression[Index];

			}
			else if (Expression[Index] == ',') {

				StringArray.push_back(Temporary);
				Temporary = "";

			}

		}

		StringArray.push_back(Temporary);

		for (unsigned int Index = 0; Index < StringArray.size(); Index++) {

			Output.push_back(SOP_INPUT::convertIntoNumber(StringArray[Index]));

		}

		unsigned int LargestNumber = GetLargestInteger(Output);

		BitsRequired = convertIntoBinaryString(LargestNumber).size();

		return Output;

	}

	
	SOP_INPUT(std::string Input = "") {

		if (Input == "") {

			LogError("No Input Provided");
			
			::exit(-1);

		}

		vArray = GetNumberArray(Input, BitsRequired);

	}

	unsigned int* GetBooleanArray() {

		unsigned int Size = pow(2, BitsRequired);

		unsigned int* Output = new unsigned int[Size];
		memset(Output, 0, Size);

		for (unsigned int Index = 0; Index < Size; Index++) {

			for (unsigned int vArrayIndex = 0; vArrayIndex < vArray.size(); vArrayIndex++) {

				if (Index == vArray[vArrayIndex]) {

					Output[Index] = 1;

				}

			}

			if (Output[Index] > 1) {

				Output[Index] = 0;

			}

		}

		return Output;

	}

};

int main(int argc, char** argw) {

	unsigned int BitsRequired = 0;

	SOP_INPUT Obj = SOP_INPUT("{1,2,3,5,7,11,13,15};");

	unsigned int* Output = Obj.GetBooleanArray();

	for (unsigned int Index = 0; Index < pow(2, Obj.BitsRequired); Index++) {

		std::cout << "Num : " << Index << " Binary : " << SOP_INPUT::convertIntoBinaryString(Index) << " Boolean : " << Output[Index] << "\n";

	}
	
}