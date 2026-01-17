# PassePasse

This simple application allows the user to safely store strong passwords on his/her local machine. It is developped with the [open-source version of Qt](https://www.qt.io/download-open-source) and it uses the [Sodium library](https://doc.libsodium.org/).

Author: Pierre Desbruns

## Features
- Generate an unpredictable password from any type of character (lower and upper cases, numbers and special characters can be chosen).
- Manage entries containing entry name, username, unpredictable password and date of last password update.
- Copy username or password to clipboard.
- Search for entries via entry name and search bar.
- Secure and simplify access to application via a single master password that can be changed when launching the app.
- Safely store entries via secret-key cryptography.
- Safely store master password via hashing.

## Install
Download [PassePasse-v2.1.0-rc.zip archive](https://github.com/PierreDesbruns/PassePasse/releases/tag/v2.1.0-rc) and extract all files.
Executable is `PassePasse.exe`. A shortcut can be created to this executable.

## Usage
Run `PassePasse.exe`. An authentication window pops up and asks for master password **(default is *1234*)**.

A correct master password gives access to the main window. All entries appear on the left. Clicking on one of them shows its details on the right part of the window.

Click on bottom left button to add an entry with desired entry name and user name. After pressing validate button, an unpredictable password is generated from desired length and character types.

Entry name, user name, and password can be edited by clicking on corresponding edit icon.

User name and password can be copied to clipboard by clicking on corresponding copy icon.

Password can be seen by clicking on see icon.

Entry names can be searched in top right search bar which is case insensitive.

A colored circle next to entries gives indication on password generation date: green for \< 3 months; orange for \< 6 months; red for \> 6 months.

Click on bottom right button to delete desired entry. This choice must be validated.

Application can be closed by simply hitting close button. Entries are saved whenever they are updated.

## Build from source
This project has been built on Windows from [Qt Creator IDE](https://www.qt.io/product/development-tools) using [MinGW](https://sourceforge.net/projects/mingw/) and [CMake](https://cmake.org/). With these tools, here are the different steps to build the application:
1. Clone this repository or download it as .zip file.
2. In Qt Creator open `src/CMakeLists.txt` file. Project should be configured correctly from `src/CMakeLists.txt.user` file.
3. Install a [Sodium pre-built library](https://download.libsodium.org/libsodium/releases/) and change path to it in `CMakeLists.txt`:
	```cmake
	# Including libsodium
	target_include_directories(${PROJECT_NAME} PRIVATE "/path/to/libsodium-win64/include")

	target_link_libraries(${PROJECT_NAME}
		PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
		PRIVATE "/path/to/libsodium-win64/lib/libsodium.a"
	)
	```
3. Build the project with release compiler. A directory called `PassePasse-v2.1.0-rc-Release` is created by Qt in parent directory of `src`.
4. Remove **all files but `PassePasse.exe`** in release directory and execute `windeployqt.exe` (located inside Qt directory, `C:\Qt\6.5.1\mingw_64\bin` for example) in a command prompt with `/path/to/PassePasse.exe` as argument.
5. Move release folder to any convenient location and set a shortcut to executable file (if needed).
6. Move the three files `default/crypto.params`, `default/entries.cipher`, and `default/master.hash` to release directory.
7. See [Usage](#usage).

> [!NOTE]
> Do not forget to copy `default/crypto.params`, `default/entries.cipher`, and `default/master.hash` files to release directory. Otherwise, you will be unable to authentify.

## License
This project is licensed under the terms of the GNU LESSER GENERAL PUBLIC LICENSE Version 3 (only). More information can be found in [LICENSE.txt](LICENSE.txt).

This project is based on Qt open-source for graphical interface and Sodium for cryptography.

### Qt
Qt modules used in this application are open-source and licensed under [GNU LESSER GENERAL PUBLIC LICENSE Version 3 (only)](https://www.gnu.org/licenses/lgpl-3.0.en.html).

Documentation for all Qt C++ classes is available [here](https://doc.qt.io/qt-6/classes.html). Clicking on a class will lead to its description and its implemented members. All members can be accessed by clicking *List of all members, including inherited members*.

Qt sources can be installed in [Qt Online Installer](https://doc.qt.io/qt-6/get-and-install-qt.html). Source packages are also available [through Git](https://doc.qt.io/qt-6/getting-sources-from-git.html), as archives in the [Qt Account](https://login.qt.io/login) (commercial users), and on [download.qt.io](https://download.qt.io/) (open-source users).

### Sodium
Sodium library is open-source and licensed under [ISC license](https://en.wikipedia.org/wiki/ISC_license).

Documentation is available [here](https://doc.libsodium.org/).

Sources are available either as [pre-compiled binaries](https://download.libsodium.org/libsodium/releases/) or via [GitHub repository](https://github.com/jedisct1/libsodium).