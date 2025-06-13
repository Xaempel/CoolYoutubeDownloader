# CoolYoutubeDowloader

This is my own youtube downloader working in local

## Disclaimer

This software is intended for **legal use only**.  
You are responsible for ensuring that you have the rights to download or access any content using this application.  
The author assumes no liability for any misuse or illegal use of this software.

## License

This project is licensed under the GNU General Public License version 2. You can find the full text of the license in the [LICENSE file.](LICENSE)

## System Requirements

[Basic Requirements]

- C++ compilator Version g++ 15.1.1 or later
- Qt Version 6 or later
- Ninja 1.12.1 or later
- CMake Version 3.20 or later
- Git Version 2.49.0 or later
- Clang-format Version 19.1.7 or later
- yt-dlp 2025.05.22 or later
- ffmpeg Version n7.1.1 or later

## Tools and Dependencies

- [CMake](https://cmake.org/): Cross-platform build system.
  [CMake Source](https://github.com/Kitware/CMake)

- [Qt](https://www.qt.io/): Cross-platform application framework.

  - Project uses the following modules Qt Widgets code for these modules can be found in the links below

  [Qt Source Archives any version](https://download.qt.io/archive/qt/)
  [Qt Source Archive version 6.0.0](https://download.qt.io/archive/qt/6.0/6.0.0/)

- [Git](https://git-scm.com/): Git is a free and open source distributed version control.
  [Git Source](https://github.com/git/git)

- [Clang-format](https://llvm.org/): A tool supplied with the Clang compiler,
  [Clang-format Source](https://github.com/llvm/llvm-project/tree/main/clang/tools/clang-format)
  [Clang-format reference](https://clang.llvm.org/docs/ClangFormat.html)

[External dependencies]

- [yt-dlp version 2025.05.22 or later](https://github.com/yt-dlp/yt-dlp): This tool is used in this project for download video from yt

  [ffmpeg source of n7.1.1](https://ffmpeg.org/releases/ffmpeg-7.1.1.tar.xz)
  - [ffmpeg](https://www.ffmpeg.org/): This project uses the ffmpeg command-line tool (version 7.1.1 or later) as an external process to handle audio and video operations.  
    You are responsible for having a legal copy of ffmpeg installed.  
    ffmpeg is licensed under either the GNU LGPL v2.1 or the GNU GPL v2 depending on its build options.  
    See the [ffmpeg licensing page](https://ffmpeg.org/legal.html) for details.
    [ffmpeg source](https://github.com/FFmpeg/FFmpeg): is available on LGPLv2.1 or GPLv2

    **This project does not include or distribute FFmpeg, it only calls the FFmpeg executable as an external program.**

## Authors

- [Xaempel]

## Contact

If you have any questions or feedback, feel free to contact me at: [xaempelfeedback@gmail.com]
