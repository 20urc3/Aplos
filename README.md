# Aplos
Aplos an extremely simple fuzzer for Windows binaries.

<a name="readme-top"></a>

<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
<br />
<div align="center">
    <h1 align="center">Aplos Fuzzer</h1>
  <p align="center">
    A simple straight-to-the-point fuzzer for Windows binaries.
  </p>
<img src=https://github.com/20urc3/Aplos/assets/94982366/3f6930f5-5be1-4e61-b917-0681be3d5f36 align="center" style="width: 35%; height: auto;">
</div>

<!-- ABOUT THE PROJECT -->
## About The Project
This tool is meant to be an educational tool allowing researcher and security enthusiast to start playing with fuzzing without having to use their brain.
The tool provide an extremely basic interface that takes a target and initial testcases folder as argument and start running a fuzzing campaign. 

Why another fuzzer ?
* Aplos fuzzer is meant to be a good reference for people without fuzzing knowledge who want to start playing with fuzzers.
* This documentation is meant to explain the core concept of fuzzing, allowing researchers to rapidly gain knowledge about the pros and cons of this technique.
* It works, as simple as it sounds it matters. Sometimes having to tweak complex tools for hours is blocking newcomers from fuzzing to try it.

Of course, this project has absolutely no pretension to replace any state-of-the-art fuzzer. On the contrary, it should be a solid foundation for you to grasp the core concept of the fuzzing techniques and then start playing with other tools later. 

<!-- Installation -->
## Installation
1. Download the latest release.
2. Extract the folder.
3. Profit!

<!-- USAGE EXAMPLES -->
## Usage
Start a command prompt and use the following syntax: 
`Aplos.exe -t {TARGET PROGRAM} -i {INPUT FOLDER} -e {EXTENSIONS} -D (OPTIONAL) {DELAY TIMEOUT}`


## Going further
As explained in this documentation, this tool is meant to be educative and help researchers learn and enjoy playing with fuzzers. 
Once you feel comfortable we invite you to try any of those wonderful projects:
* [WTF Snapshot fuzzer][wtf-url]
* [WinAFL][wafl-url]
* [Jackalope][jck-url]

<!-- Dependencies -->
## Dependencies
This project is only possible because of the (great) work other people have provided. 
- The mutation engine used: [Radamsa](https://gitlab.com/akihe/radamsa)
- The CLI argument parser used: [CLI11](https://github.com/CLIUtils/CLI11)

<!-- CONTRIBUTING -->
## Contributing
Any contributions you make are **greatly appreciated**. If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement". Don't forget to give the project a star! Thanks again! 

That being said, this project will still be improved and modified over time. People are more than welcome to contribute with one very important philosophy: it **must** stay simple to use. 

<!-- ROADMAP -->
## Roadmap
- [ ] File management: When reaching > 3 gen, starting to delete unused input files.
- [ ] Add instrumentation to record coverage.
- [ ] Allow persistent mode.
- [ ] Integrate AFL like mutation engine.
See the [open issues](https://github.com/20urc3/Aplos/issues) for a full list of proposed features (and known issues).

<!-- ACKNOWLEDGMENTS -->
## Acknowledgment
Short (non-exhaustive) list of amazing people and project that inspired me during this project.
- People:
    * [@corelanc0d3r](https://twitter.com/corelanc0d3r)
    * [@0vercl0k](https://twitter.com/0vercl0k)
    * [@Richard Johnson](https://twitter.com/richinseattle)
    * [@Ivan Fratic](https://twitter.com/ifsecure)
    * [@Vanhaussuer-thc](https://twitter.com/hackerschoice)
- Projects:
    * [Fuzzing.io training](https://www.fuzzing.io/)
    * [Gamozolabs YT channel](https://www.youtube.com/@gamozolabs)
    * [GynvaelEN YT channel](https://www.youtube.com/@GynvaelEN)
    * [AFL++](https://github.com/AFLplusplus/AFLplusplus)
    * [Domato: DOM Fuzzer](https://github.com/googleprojectzero/domato)

## Authors
Author: [@2ourc3](https://twitter.com/2ourc3)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->

[contributors-shield]: https://img.shields.io/github/contributors/20urc3/Aplos.svg?style=for-the-badge
[contributors-url]: https://github.com/20urc3/Aplos/graph/contributors
[forks-shield]: https://img.shields.io/github/forks/20urc3/Aplos.svg?style=for-the-badge
[forks-url]: https://github.com/20urc3/Aplos/network/members
[stars-shield]: https://img.shields.io/github/stars/20urc3/Aplos.svg?style=for-the-badge
[stars-url]: https://github.com/20urc3/Aplos/stargazers
[issues-shield]: https://img.shields.io/github/issues/20urc3/Aplos.svg?style=for-the-badge
[issues-url]: https://github.com/20urc3/Aplos/issues
[license-shield]: https://img.shields.io/github/license/20urc3/Aplos.svg?style=for-the-badge
[license-url]: https://github.com/20urc3/Aplos/blob/master/LICENSE.txt

[wtf-url]: https://github.com/0vercl0k/wtf
[wafl-url]: https://github.com/googleprojectzero/winafl
[jck-url]: https://github.com/googleprojectzero/Jackalope
