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
        <li><a href="#building-visual-studio-code">Building (Visual Studio Code)</a></li>
        <li><a href="#building-manual">Building (Manual)</a></li>
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

The final output will be in a file called `output.csv` and the format for each transaction will be:

`"<ACCOUNT NUMBER (truncated)>","<TRANSACTION DATE>","<ID>","<TRANSACTION NAME>","<CURRENCY AMOUNT>"`.

For example:

`"1234","04/18/2023","78G41DS8VD89SF891","MCDONALDS RESTAURANT","-15.34"`.

It will also create these files:

- <code>logs.txt</code> - These are the application logs. Refer to them if the CSV file wasn't generated or there were other problems during execution.
- <code>skipped_files.txt</code> - This is a list of files that the tool skipped. A common error is that the statement file was renamed after download. Do not rename them.
- <code>skipped_lines.txt</code> - This is a list of the individual lines in the statement that were skipped. Refer to this if there were any missing items in the final CSV file. It will only add lines that were possibly relevant i.e. had dollar symbols, had numbers, etc.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Built With

- [![C++][C++]][C++-url]
- [![pdfium][pdfium]][pdfium-url]
- [![CMake][CMake]][CMake-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->

## Getting Started

Pre-built exectuables will be provided in the future, but for now the project must be built locally. Please follow the instructions below to build the program.

### Prerequisites

- A C++ compiler.
- CMake.

### Building (Visual Studio Code)

The project can be built using Microsoft's CMake extension for VSCode.

<ol>
  <li>
    Clone this repo, along with the submodules.</br>
    <code>git clone --recurse-submodules https://github.com/ryan-kawano/Bank_Statement_Converter</code>
  </li>

  <li>
    Open the cloned project in VSCode.
  </li>

  <li>
    Install the <a href="https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools">CMake Tools Extension</a> for VSCode.
  </li>

  <li>
    Open the CMake side-panel (usually on the left-hand side).
  </li>

  <li>
    Go through the flow provided in the menu.</br>
    <code>Configure -> Build</code>
  </li>
</ol>

### Building (Manual)

<ol>
  <li>
    Clone this repo, along with the submodules.</br>
    <code>git clone --recurse-submodules https://github.com/ryan-kawano/Bank_Statement_Converter</code>
  </li>

  <li>
    From the root of this project, make a build directory.</br>
    <code>mkdir build</code>
  </li>

  <li>
    Generate the build system using the provided CMake files. From the <code>build</code> directory that was created in the previous step, execute the command below. You may specify a build system in the command or let CMake use the default one for your system.</br>
    <code>cmake ..</code>
  </li>

  <li>
    Build the project by running the command below from the <code>build</code> directory.</br>
    <code>cmake --build . -j</code>
  </li>
</ol>

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE -->

## Usage

<ol>
  <li>Navigate to the directory where the program is.</li>
  <li>In the same directory as the compiled executable, create a directory called <code>statements</code>.</li>
  <li>Place the PDF statements that you want converted into <code>statements</code>.</li>
  <li><strong>Optional:</strong> Copy the config file located <a href=src/configuration/config.yaml>here</a> into the same directory that the executable is in. Modify the settings as you wish.</li>
  <li>Run the executable by double-clicking it.</li>
  <li>A folder called <code>output</code> will be created. Inside it will be the final CSV file(s) and other logs from execution.</li>
</ol>

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->

## Acknowledgments

- [Best-README-Template](https://github.com/othneildrew/Best-README-Template) for this README template.
- [pdfium](https://pdfium.googlesource.com/pdfium/) for parsing PDF statements.
<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->

[C++]: https://img.shields.io/badge/-C++-blue?logo=cplusplus
[C++-url]: https://en.wikipedia.org/wiki/C%2B%2B
[pdfium]: https://img.shields.io/badge/pdfium-blue
[pdfium-url]: https://pdfium.googlesource.com/pdfium
[CMake]: https://img.shields.io/badge/CMake-064F8C?logo=cmake&logoColor=fff
[CMake-url]: https://cmake.org/
