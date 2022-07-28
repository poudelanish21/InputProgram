#include <iostream>
#include <chrono>
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

	unsigned int* Array = new unsigned int[16];
	unsigned int ArrayCounter = 0;

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

	unsigned int* _convertToArray(std::string Input, unsigned int& NumberOfBitsRequired) {

		unsigned int Size = Input.size();

		char Operators[4] = { '}', '{', ';', ' ' };

		bool Number = false;
		
		bool Stop;

		char temp[9];
		memset(temp, 0, 9);
		unsigned int TempCounter = 0;

		for (unsigned int Index = 0; Index < Size; Index++) {

			Stop = false;

			for (unsigned int OperatorIndex = 0; OperatorIndex < 4; OperatorIndex++) {

				if(Input[Index] == Operators[OperatorIndex])
					Stop = true;

			}

			if (!Stop) {

				temp[TempCounter] = Input[Index];
				TempCounter++;

			}
			else {

				Array[ArrayCounter] = convertIntoNumber(temp);
				ArrayCounter++;

				TempCounter = 0;
				memset(temp, 0, 9);

			}

		}

	}
	SOP_INPUT(std::string Input = "") {

		if (Input == "") {

			LogError("No Input Provided");
			
			::exit(-1);

		}

		unsigned int NumberOfBitsRequired = 0;

		_convertToArray(Input, NumberOfBitsRequired);

	}

};

int main(int argc, char** argw) {

	SOP_INPUT("{0,1,2,3,4,5,6,7};")
	
}