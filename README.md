# Android JavaScriptCore
This project allows you to execute JavaScript scripts and use two-way bound objects (native-JS) in your apps. It uses Apple's JavaScriptCore engine and is based on the Eric Lange's JNI wrapper [AndroidJSCore] (https://github.com/ericwlange/AndroidJSCore). At some point Eric decided to discontinue the development of his project. This inspired me to start this project. The key differences is:
1. It contains the latest version of the JS Core library.
2. Easy java objects export.
3. Java properties export with the two-way binding.
4. Useful Java-JS entities conversion methods.
5. General improvements of the initial project.

The main benefit of using this project is the ability to use a single code base of the most popular programming language for the business logic on the cross platform apps. And the usage of the JavaScriptCore engine brings the predictable behavior on both iOS and Android devices.
