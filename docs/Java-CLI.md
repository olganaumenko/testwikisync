# UnitTestBot Java command-line interface (CLI)

UnitTestBot Java CLI allows you to automatically generate human-readable ready-to-use unit tests for Java code. 
With CLI, you can streamline manual unit testing or integrate UnitTestBot Java into your CI/CD 
process.

UnitTestBot Java CLI is distributed as a [JAR](https://github.com/UnitTestBot/UTBotJava/actions/runs/5221394489) file. You can find the implementation in the [utbot-cli](https://github.com/UnitTestBot/UTBotJava/tree/main/utbot-cli) module.

Check the tutorial to get started with UnitTestBot Java CLI (examples are provided for Windows):

<!-- TOC -->
  * [System requirements](#system-requirements)
  * [How to download](#how-to-download)
  * [How to generate tests for a single class](#how-to-generate-tests-for-a-single-class)
  * [How to generate tests for multiple classes](#how-to-generate-tests-for-multiple-classes)
  * [How to run tests](#how-to-run-tests)
  * [Commands, options, arguments](#commands-options-arguments)
<!-- TOC -->

## System requirements

* JDK 17: installed.
* JAVA_HOME: contains the path to JDK 17 installation directory, e.g., `C:\Program Files\Java\jdk-17`.
* PATH: contains the path to the `bin` folder of the JDK 17 installation directory, e.g., `C:\Program 
  Files\Java\jdk-17\bin`.

## How to download

1. Go to [UnitTestBot Java builds](https://github.com/UnitTestBot/UTBotJava/actions/workflows/build-and-run-tests.yml).
2. Find the latest “green” build for `main`, e.g., try this valid [one](https://github.com/UnitTestBot/UTBotJava/actions/runs/5221394489).
3. Scroll down to **Artifacts** and download the zip-archive named like `utbot-cli-java-main-VERSION`.
4. Create a directory (e.g., `utbot`) and unzip the archive into it.

## How to generate tests for a single class

You may keep your source and test files as well as the `utbot-cli-java-main-VERSION.jar` file anywhere you like, but 
you should specify the proper paths as options. To keep it simple, we locate everything in one place.

1. In your new directory with the `utbot-cli-java-main-VERSION.jar` inside, create an `src` folder for your source 
   files 
   under test, a `build` folder for the complied `.class` files, and a `test` folder for the resulting tests, e.g.:
```   
└── utbot
    ├── build
    ├── src
        ├── BitOperators.java
    ├── test
    ├── utbot-cli-java-main-VERSION.jar
```
2. Compile the source `.java` file and put the resulting `.class` file into the `build` folder, e.g.:
```shell
javac src\BitOperators.java -d build
```
Now you have this:
```   
└── utbot
    ├── build (path to compiled source or test classes)
        ├── org
            ├── utbot
                ├── examples
                    ├── math
                        ├── BitOperators.class
    ├── src
        ├── BitOperators.java (source file)
    ├── test (path for test file)
    ├── utbot-cli-java-main-VERSION.jar
```
3. Generate tests for the chosen source file using the `generate` command (refer to the upper tree to understand the 
   relevant paths):
 ```shell
java -jar utbot-cli-main-VERSION.jar generate --source <path to source file> --classpath <path to compiled source class> --output <test file with path> <TARGETCLASSFQN: fully qualified name for source class>
```
Example:
```shell
java -jar utbot-cli-main-2023.6.4550.jar generate -s src\BitOperators.java -cp build -o test\BitOperatorsTest.java org.utbot.examples.math.BitOperators
```
Make sure you use the `--source, -s` and `--classpath, -cp` required options and pass the `TARGETCLASSFQN` argument, 
which is the target class fully qualified name. 
We recommend using the`--output, -o` option for consistency.

## How to generate tests for multiple classes

1. Keep the source files in the `src` folder.
2. Compile the source `.java` files and put the resulting `.class` files into the `build` folder.
3. Generate tests for the chosen source files using the `bunchGenerate` command:

```shell
java -jar utbot-cli-main-VERSION.jar bunchGenerate --classpath <path to compiled source classes> --output <path to test files> --filter <package to test> <CLASSROOTDIRECTORY: path to compiled source classes>
```
Example:
```shell
java -jar utbot-cli-main-2023.6.4550.jar bunchGenerate -cp build -o test -pf org.utbot.examples.math build
```
Make sure you use the `--classpath, -cp` required option and pass the `CLASSROOTDIRECTORY` argument, which is the 
folder containing the compiled source classes.
We recommend using the`--output, -o` option for consistency.

With the `--filter, -pf` option, you can specify the source files to generate tests for. If the fully qualified name of 
the given source class contains the specified string, the tests are generated for this class.

## How to run tests

1. Compile the generated test and put the resulting `.class` file into the `build` folder, e.g.:
```shell
javac -cp build;utbot-cli-main-2023.6.4550.jar -d build test\BitOperatorsTest.java
```
Make sure to include the following paths to the classpath:
* the path to the folder where you put the compiled `.class` files, e.g., `build`;
* the path to a test framework library (JUnit 4, JUnit 5, TestNG) or the `utbot-cli-java-main-VERSION.jar` file.

Now you have this:
```   
└── utbot
    ├── build
        ├── org
            ├── utbot
                ├── examples
                    ├── math
                        ├── BitOperators.class
                        ├── BitOperatorsTest.class
    ├── src
        ├── BitOperators.java
    ├── test
        ├── BitOperatorsTest.java
    ├── utbot-cli-java-main-VERSION.jar
```
2. Run the compiled test class:
```shell
java -jar utbot-cli-main-VERSION.jar run --classpath <path to compiled test class> <fully qualified name for test class>
```
Example:
```shell
java -jar utbot-cli-main-2023.6.4550.jar run -cp build org.utbot.examples.math.BitOperatorsTest
```

## Commands, options, arguments

Basic usage for UnitTestBot Java CLI requires you to specify commands, options, and arguments:
```shell
java -jar utbot-cli-main-VERSION.jar [GENERAL OPTIONS] COMMAND [COMMAND OPTIONS] ARGS
```

### General options

| Option      | Value                                       | Effect                                      |
|-------------|---------------------------------------------|---------------------------------------------|
| --verbosity | [ERROR \| WARN \| INFO \| DEBUG \| TRACE]   | Change verbosity level (case-insensitive).  |
| --version   |                                             | Show UnitTestBot Java CLI version and exit. |
| -h, --help  |                                             | Show help message and exit.                 |


### Command usage, options and arguments: `generate`

Generate tests for the specified class:
```shell
java -jar utbot-cli-main-VERSION.jar [GENERAL OPTIONS] generate [COMMAND OPTIONS] TARGETCLASSFQN
```
`TARGETCLASSFQN` — target class fully qualified name.

| Option                     | Value                                            | Effect                                                                                                                                                                                                                                                                 |
|----------------------------|--------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| -m, --mock-strategy        | [do-not-mock \| package-based \| all-except-cut] | Define the mocking strategy                                                                                                                                                                                                                                            |
| --test-framework           | [junit4 \| junit5 \| testng]                     | Test framework to be used                                                                                                                                                                                                                                              |
| --mock-statics             | [do-not-mock-statics \| mock-statics]            | Choose framework for mocking statics (or not mock statics at all                                                                                                                                                                                                       |
| -f, --force-static-mocking | [force \| do-not-force]                          | Forces mocking static methods and constructors for "--mock-always" classes                                                                                                                                                                                             |
| --overflow                 | [ignore \| error]                                | Treat overflows as errors                                                                                                                                                                                                                                              |
| --mock-always, --ma        | TEXT                                             | Classes fully qualified name to force mocking theirs static methods and constructors</br> (you can use it multiple times to provide few classes)</br>default classes =</br>java.util.Random org.slf4j.Logger</br>org.slf4j.LoggerFactory</br>org.utbot.api.mock.UtMock |
| --generation-timeout       | INT                                              | Specifies the maximum time in milliseconds used to generate tests (1200000 by default)                                                                                                                                                                                 |
| -o, --output               | TEXT                                             | Specifies output file for a generated test                                                                                                                                                                                                                             |
| -cp, --classpath           | TEXT                                             | Specifies the classpath for a class under test                                                                                                                                                                                                                         |
| -s, --source               | TEXT                                             | Specifies source code file for a generated test                                                                                                                                                                                                                        |
| --project-root             | TEXT                                             | Specifies the root of the relative paths in the sarif report that are required to show links correctly                                                                                                                                                                 |
| --sarif                    | TEXT                                             | Specifies output file for the static analysis report                                                                                                                                                                                                                   |
| -l, --language             | [Java \| Kotlin]                                 | Defines the codegen language                                                                                                                                                                                                                                           |
| -p, --print-test           |                                                  | Specifies whether a test should be printed out to StdOut                                                                                                                                                                                                               |
| -h, --help                 |                                                  | Show this message and exit                                                                                                                                                                                                                                             |

### Command usage, options and arguments: `bunchGenerate`

Generate tests for class files in the specified directory.
```shell
java -jar utbot-cli-main-VERSION.jar [GENERAL OPTIONS] bunchGenerate [COMMAND OPTIONS] CLASSROOTDIRECTORY
```
`CLASSROOTDIRECTORY` — directory with classes.

| Option                    | Value                                            | Effect                                                                                                                                                                                                                                                              |
|---------------------------|--------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| -m, --mock-strategy       | [do-not-mock \| package-based \| all-except-cut] | Defines the mock strategy                                                                                                                                                                                                                                           |
| --test-framework          | [junit4 \| junit5 \| testng]                     | Test framework to be used                                                                                                                                                                                                                                           |
| --mock-statics            | [do-not-mock-statics \| mock-statics]            | Choose framework for mocking statics (or not mock statics at all                                                                                                                                                                                                    |
| f, --force-static-mocking | [force \| do-not-force]                          | Forces mocking static methods and constructors for "--mock-always" classes                                                                                                                                                                                          |
| --overflow                | [ignore \| error]                                | Treat overflows as errors                                                                                                                                                                                                                                           |
| --mock-always, --ma       | TEXT                                             | Classes fully qualified name to force mocking theirs static methods and constructors</br>(you can use it multiple times to provide few classes);default classes = </br> java.util.Random org.slf4j.Logger</br>org.slf4j.LoggerFactory</br>org.utbot.api.mock.UtMock |
| --generation-timeout      | INT                                              | Specifies the maximum time in milliseconds used to generate tests (1200000 by default)                                                                                                                                                                              |
| -cp, --classpath          | TEXT                                             | Specifies the classpath for a class under test                                                                                                                                                                                                                      |
| -o, --output              | TEXT                                             | Specifies output directory. It will be populated with package-directory structure.                                                                                                                                                                                  |
| -pf, --filter             | TEXT                                             | Specifies a string to generate tests only for classes that contains the substring in the fully qualified name                                                                                                                                                       |
| --classpathFile           | TEXT                                             | Specifies the classpath as a list of strings in a file                                                                                                                                                                                                              |
| -l, --language            | [Java \| Kotlin]                                 | Defines the codegen language                                                                                                                                                                                                                                        |
|  -h, --help               |                                                  | Show this message and exit                                                                                                                                                                                                                                          |

### Command usage, options and arguments: `run`

Runs tests for the specified class.
```shell
java -jar utbot-cli-main-VERSION.jar run [GENERAL OPTIONS] run [COMMAND OPTIONS] CLASSWITHTESTSNAME
```
`CLASSWITHTESTSNAME` — specifies a class with tests.

| Option           | Value                        | Effect                                                                   |
|------------------|------------------------------|--------------------------------------------------------------------------|
| -cp, --classpath | TEXT                         | Specifies the classpath for a class with tests                           |
| --test-framework | [junit4 \| junit5 \| testng] | Test framework to be used                                                |
| -o, --output     | TEXT                         | Specifies output file with specified extension for tests run information |
| -h, --help       |                              | Show this message and exit                                               |
