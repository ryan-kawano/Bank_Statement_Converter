# Wells Fargo Statement PDF to CSV Converter
A tool for converting Wells Fargo bank statements in PDF format to CSV format. Statements in CSV format are easier to handle and parse, so this tool aims to act as an intermediate step to convert statements into an easier-to-use format, for further use in other applications.

The application can handle multiple PDF statements at once. It will parse through them, sort them by date, and will combine all of them into a single CSV file. Currently, it only processes transactions that had a subtractive impact on the account i.e. purchases, withdrawals, and interest charge on purchases (if it was a credit card statement). This means it will skip any credits, deposits into the account, etc. I plan to update the tool in the future to parse this data as well.

The final output will be in a file called `combined_statements.csv` and the format for each transaction will be:
`"<LAST FOUR NUMBERS OF ACCOUNT>","TRANSACTION DATE","REFERENCE NUMBER","TRANSACTION NAME","CURRENCY AMOUNT"`.
For example:
`"1234","04/18/2023","78G41DS8VD89SF891","MCDONALDS RESTAURANT","-15.34"`
It will also create these files in `output`:
* logs.txt - These are the application logs. Refer to them if the CSV file wasn't generated or there were other problems during execution.
* skipped_files.txt - This is a list of files that the tool skipped. Usually, it is because the PDF statement's file name didn't have the correct format.
* skipped_lines.txt - This is a list of the individual lines in the statement that it skipped. Refer to this if there were any missing items in the final CSV file. It will only add lines that were possibly relevant i.e. had dollar symbols, had numbers, etc.

## Usage
In order to use the tool, follow the steps below:
1. Download the executable file `Wells Fargo Statement PDF to CSV Converter.exe` from the `bin` directory of this repository. Currently, only the Windows executable is provided. In the future, I plan to compile the project for other platforms. You may compile the project for your preferred platform by yourself, if you wish.
2. Create a new folder somewhere on your computer. For this example, it will be called `wells_fargo_converter`.
3. Put the downloaded executable file in the folder.
4. Create a folder within `wells_fargo_converter` called `statements_pdf`. The name of the folder must match exactly, including the casing.
5. Put the PDF statements, that you want converted, into `statements_pdf`. **Do not rename the files after downloading them from Wells Fargo**. The program extracts the date from the file name. They should be in the form `MMDDYY WellsFargo.pdf`, for example, `011524 WellsFargo.pdf`. If you renamed it, simply rename it back to match the format. It should be the date that the statement was posted.
6. Run the executable by double-clicking it.
7. A folder called `output` will be created. Inside it will be the final CSV file and other logs from execution.

## Building the project
### Prerequisites
* Poppler library. This is used for parsing the PDF files.

### Building
Use a C++ compiler of your choice and compile the source files along with the `RK_Logger` submodule.

## Notes
* This is a work-in-progress. New features are still being added and existing features are still being updated.