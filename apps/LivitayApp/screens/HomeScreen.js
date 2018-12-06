import React from 'react';
import {
  Image,
  Platform,
  ScrollView,
  StyleSheet,
  Text,
  TouchableOpacity,
  View,
} from 'react-native';
import { WebBrowser } from 'expo';

import { MonoText } from '../components/StyledText';

export default class HomeScreen extends React.Component {
  static navigationOptions = {
    header: null,
  };

  render() {
    return (
      <View style={styles.container}>
        <ScrollView style={styles.container} contentContainerStyle={styles.contentContainer}>
          <View style={styles.contentContainer}>
            <Image
              source={require('../assets/images/logoSmall.png')}
              style={styles.welcomeImage}
            />
          </View>

          <View style={styles.contentContainer}>
            <Text style={styles.mainText}>'Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body Main body '</Text>
          </View>
        </ScrollView>

        <View style={styles.tabBarContainer}>
          <TouchableOpacity onPress={this._handleWebsitePress} style={styles.websiteLink}>
              <Text style={styles.websiteLinkText}>Here is our website!</Text>
            </TouchableOpacity>
        </View>
      </View>
    );
  }

  _handleWebsitePress = () => {
    WebBrowser.openBrowserAsync(
      'https://www.livitay.com'
    );
  };
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
  },
  contentContainer: {
    alignItems: 'center',
    paddingTop: 10,
  },
  welcomeImage: {
    width: 200,
    height: 160,
    resizeMode: 'contain',
    marginTop: 0, //may need adj
    marginLeft: -10,
  },
  tabBarContainer: {
    position: 'absolute',
    bottom: 0,
    left: 0,
    right: 0,
    ...Platform.select({
      ios: {
        shadowColor: 'black',
        shadowOffset: { height: -3 },
        shadowOpacity: 0.2,
        shadowRadius: 3,
      },
      android: {
        elevation: 20,
      },
    }),
    alignItems: 'center',
    backgroundColor: '#fbfbfb',
    paddingVertical: 10,
  },
  websiteLink: {
    paddingVertical: 10,
  },
  websiteLinkText: {
    fontSize: 14,
    color: '#2e78b7',
  },
  mainText: {
    fontSize: 16,
    color: '#fe000a',
    marginLeft: 16,
    marginBottom: 60, //may need adj
  },
});
