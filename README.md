<a id="readme-top"></a>

<div>
<h3 align="center">Bank Statement Converter</h3>

  <p align="center">
    A tool to convert bank statements from human-readable formats to formats that are more machine-friendly.
    <br />
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#features">Features</a>
    </li>
    <li>
        <a href="#currently-supported-banks-and-formats">Currently Supported Banks and Formats</a>
    </li>
    <li>
        <a href="#output">Output</a>
    </li>
    <li>
      <a href="#built-with">Built With</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#building">Building</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->

## About The Project

<strong>Bank Statement Converter</strong> is a tool that converts bank statements from human-readable formats like <strong>PDF (Portable Document Format)</strong> to formats that are more machine-friendly like <strong>CSV (Comma-Separated Values)</strong>. This tool aims to be an intermediary step to get statements in a usable format, before doing any further processing.

<strong>Note: This program has no official affiliation with any bank.</strong>

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Features

- <strong>Statement Converter</strong> - Converts statements.
- <strong>Multi-statement Processing</strong> - Able to process multiple statements at once and combine them all into a single file.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Currently Supported Banks and Formats

<ul>
  <li>Wells Fargo
    <ul>
      <li>PDF -> CSV</li>
    </ul>
  </li>
</ul>

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Output

The final output will be in a file called `combined_statements.csv` and the format for each transaction will be:

`"<LAST FOUR NUMBERS OF ACCOUNT>","TRANSACTION DATE","REFERENCE NUMBER","TRANSACTION NAME","CURRENCY AMOUNT"`.

For example:

`"1234","04/18/2023","78G41DS8VD89SF891","MCDONALDS RESTAURANT","-15.34"`.

It will also create these files:

- <code>logs.txt</code> - These are the application logs. Refer to them if the CSV file wasn't generated or there were other problems during execution.
- <code>skipped_files.txt</code> - This is a list of files that the tool skipped. A common error is that the statement file was renamed after download. Do not rename them.
- <code>skipped_lines.txt</code> - This is a list of the individual lines in the statement that were skipped. Refer to this if there were any missing items in the final CSV file. It will only add lines that were possibly relevant i.e. had dollar symbols, had numbers, etc.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Built With

- [![C++][C++]][C++-url]
- [![Poppler][Poppler]][Poppler-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->

## Getting Started

You may either download the compiled program from the release section of this GitHub page or build the program by following the instructions below.

### Prerequisites

- A C++ compiler.
- The Poppler library installed locally.

### Building

<ol>
  <li>Clone this repo, along with the submodules.

<code>git clone --recurse-submodules https://github.com/ryan-kawano/Bank_Statement_Converter</code>

  </li>
  <li>Build the project in Visual Studio Code using the provided VS Code setting files <a href=".vscode/launch.json">launch.json</a> and <a href=".vscode/tasks.json">tasks.json</a>. They might need to be updated based on what compiler you are using and where you have Poppler installed. I recommend getting it from MSYS2 in order to match the files.</li>
</ol>

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE -->

## Usage

<ol>
  <li>Navigate to the directory where the program is.</li>
  <li>In the same directory as the compiled executable, create a directory called <code>statements_pdf</code>.</li>
  <li>Place the PDF statements that you want converted into <code>statements_pdf</code>. <strong>Do not rename the files after downloading them</strong>. The program extracts information such as the date from the file name.</li>
  <li>Run the executable by double-clicking it.</li>
  <li>A folder called <code>output</code> will be created. Inside it will be the final CSV file and other logs from execution.</li>
</ol>

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->

## Acknowledgments

- [Best-README-Template](https://github.com/othneildrew/Best-README-Template) for this README template.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->

<!-- [contributors-shield]: https://img.shields.io/github/contributors/ryan-kawano/RK_Logger.svg?style=for-the-badge
[contributors-url]: https://github.com/ryan-kawano/RK_Logger/graphs/contributors
[issues-shield]: https://img.shields.io/github/issues/ryan-kawano/RK_Logger.svg?style=for-the-badge
[issues-url]: https://github.com/ryan-kawano/RK_Logger/issues -->

[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: http://www.linkedin.com/in/ryan-kawano-74bab922b
[product-screenshot]: images/screenshot.png
[C++]: https://img.shields.io/badge/-C++-blue?logo=cplusplus
[C++-url]: https://en.wikipedia.org/wiki/C%2B%2B
[Poppler]: https://img.shields.io/badge/Poppler-blue.svg?style=flat-square
[Poppler-url]: https://poppler.freedesktop.org/
