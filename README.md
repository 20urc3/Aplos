<!-- PROJECT SHIELDS -->
<div align="center">
    <h1 align="center">Aplos Fuzzer</h1>
<img src="https://img.shields.io/circleci/project/github/badges/shields/master" alt="build status"></a>
<img src="https://img.shields.io/badge/version-0.1-blue"></a>
    <p align="center">
    A simple straight-to-the-point fuzzer for Windows binaries.
  </p>
<img src=https://github.com/20urc3/Aplos/assets/94982366/3f6930f5-5be1-4e61-b917-0681be3d5f36 align="center" style="width: 35%; height: auto;">
</div>

<!-- ABOUT THE PROJECT -->
## About The Project
This tool is meant to be an educational tool allowing researchers and security enthusiasts to start playing with fuzzing without having to use their brain.
The tool provides an extremely basic interface that takes a target and an initial testcases folder as arguments and starts running a fuzzing campaign. 

Why another fuzzer ?
* Aplos fuzzer is meant to be a good reference for people without fuzzing knowledge that want to start playing with fuzzers.
* This documentation is meant to explain the core concepts of fuzzing, allowing researchers to rapidly gain knowledge about the pros and cons of this technique.
* It works, as simple as it sounds, and it matters. Sometimes having to tweak complex tools for hours is blocking newcomers from trying out fuzzing.

Of course, this project has absolutely no pretension to replace any state-of-the-art fuzzer. On the contrary, it should be a solid foundation for you to grasp the core concept of the fuzzing techniques and then start playing with other tools later. 

<!-- Installation -->
## Installation
1. Download the latest release.
2. Extract the folder.
3. Profit!

<!-- USAGE EXAMPLES -->
## Usage
<div align="center">
<img src=https://github.com/20urc3/Aplos/assets/94982366/989e0a88-50bd-47e0-b39e-a2a2970daee9 align="center">
</div>
<br />
  
Start the fuzzer using the following syntax: 
```sh
Aplos.exe -t {TARGET PROGRAM} -i {INPUT FOLDER} -e {EXTENSIONS} -D (OPTIONAL) {DELAY TIMEOUT}`
```
* `-t, --target`: The path the target program you want to fuzz.
* `-i, --input`: The input folder containing your testcases.
* `-e, --extension`: The extensions your mutated file should use.
* `-D, --delay`: The delay in ms for the target program to be executed then close (default = 1000).  

## Going further
As explained in this documentation, this tool is meant to be educative and help researchers learn and enjoy playing with fuzzers. 
Once you feel comfortable, we invite you to try any of those wonderful projects:
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

[wtf-url]: https://github.com/0vercl0k/wtf
[wafl-url]: https://github.com/googleprojectzero/winafl
[jck-url]: https://github.com/googleprojectzero/Jackalope
