import { View, Image, StyleSheet, Dimensions } from "react-native";
import Background from "../components/Background";
import Cabinet from "../components/Cabinet";
import BigButton from '../components/BigButton';

const { width } = Dimensions.get("window");

/**
 * MainScreen component - the main view of the application.
 * It consists of:
 * 1. Background - a visual layer behind other components.
 * 2. Top section - contains the company logo (and potentially settings button).
 * 3. Middle section - contains the Cabinet component (glass cabinet controller).
 * 4. Bottom section - contains a BigButton to toggle cabinet power.
 *
 * @param {object} navigation - React Navigation prop for screen navigation.
 * @returns {JSX.Element} The structured UI for the main screen.
 */
export default function MainScreen({ navigation }) {
    return (
        <View style={styles.container}>
            <Background/>
            <View style={styles.top}>
              <View style={{flex: 4, alignItems: 'center', justifyContent: 'flex-start'}}>
                <Image 
                  style={styles.tiny_logo}
                  source={require('../assets/zf-logo.png')}
                />
              </View>
            </View>
            <View style={styles.mid}>
              <Cabinet/>
            </View>
            <View style={styles.bot}>
              <View style={styles.buttonBox}>
                <BigButton text="Wyłącz" altText="Włącz" />
              </View>
            </View>
        </View>
    );
}

const styles = StyleSheet.create({
    container: {
        flex: 1,
        alignItems: 'center',
        justifyContent: 'center',
    },
    text: {
        fontSize: 24,
        fontWeight: 'bold',
        marginBottom: 16,
    },
    tiny_logo: {
      resizeMode: 'contain',
      width: width / 6,
      height: width / 6,
    },
    buttonBox: {
      justifyContent: "center",
      alignItems: "center",
      height: '50%',
      width: '100%',
    },
    top: {
      flex: 8,  // Top section height
      justifyContent: "center",
      alignItems: "center",
      width: '100%',
      marginTop: '10%',
      flexDirection: 'row', // Align items in a row
    },
    mid: {
      flex: 32,  // Middle section height
      justifyContent: "center",
      alignItems: "center",
      width: '100%',
    },
    bot: {
      flex: 10,  // Bottom section height
      justifyContent: "center",
      alignItems: "center",
      width: '100%',
    },
});
