
# react-native-sunfish

## Getting started

`$ npm install react-native-sunfish4 --save`

### Mostly automatic installation

`$ react-native link react-native-sunfish4`

### Manual installation


#### iOS

1. In XCode, in the project navigator, right click `Libraries` ➜ `Add Files to [your project's name]`
2. Go to `node_modules` ➜ `react-native-sunfish` and add `RNSunfish.xcodeproj`
3. In XCode, in the project navigator, select your project. Add `libRNSunfish.a` to your project's `Build Phases` ➜ `Link Binary With Libraries`
4. Run your project (`Cmd+R`)<

#### Android

1. Open up `android/app/src/main/java/[...]/MainActivity.java`
  - Add `import com.reactlibrary.RNSunfishPackage;` to the imports at the top of the file
  - Add `new RNSunfishPackage()` to the list returned by the `getPackages()` method
2. Append the following lines to `android/settings.gradle`:
  	```
  	include ':react-native-sunfish'
  	project(':react-native-sunfish').projectDir = new File(rootProject.projectDir, 	'../node_modules/react-native-sunfish/android')
  	```
3. Insert the following lines inside the dependencies block in `android/app/build.gradle`:
  	```
      compile project(':react-native-sunfish')
  	```

#### Windows
[Read it! :D](https://github.com/ReactWindows/react-native)

1. In Visual Studio add the `RNSunfish.sln` in `node_modules/react-native-sunfish/windows/RNSunfish.sln` folder to their solution, reference from their app.
2. Open up your `MainPage.cs` app
  - Add `using Sunfish.RNSunfish;` to the usings at the top of the file
  - Add `new RNSunfishPackage()` to the `List<IReactPackage>` returned by the `Packages` method


## Usage
```javascript
import RNSunfish from 'react-native-sunfish';

// TODO: What to do with the module?
RNSunfish;
```
