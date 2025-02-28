import React, { useState } from "react";
import { View, Text, TouchableOpacity, StyleSheet } from "react-native";
import { useFonts } from "expo-font";
import AppLoading from "expo-app-loading";
import colors from "../constants/colors";
import toggleCabinet from "../toggleObjects/ToggleCabinet"; // Import the singleton

/**
 * A large toggle button component.
 * 
 * This component renders a large button that toggles the state of a cabinet 
 * when pressed. It uses a singleton (`toggleCabinet`) to manage the state 
 * and force a re-render when the state changes.
 * 
 * @param {Object} props - Component props.
 * @param {string} props.text - Text displayed on the button when the cabinet is ON.
 * @param {string} props.altText - Text displayed on the button when the cabinet is OFF.
 * 
 * @returns {JSX.Element} A styled toggle button.
 */
const BigButton = ({ text, altText }) => {
  // State used to force a re-render when the toggle state changes
  const [_, forceUpdate] = useState(false);

  /**
   * Handles button click event.
   * Toggles the cabinet state and forces a component re-render.
   */
  const handlerClick = () => {
    toggleCabinet.turnState((prev) => !prev);
    forceUpdate((prev) => !prev); // Force re-render
  };

  // Load custom font
  const [fontsLoaded] = useFonts({
    CustomFont: require("../fonts/Prometo_Trial_Md.ttf"),
  });

  // Show loading screen until fonts are loaded
  if (!fontsLoaded) {
    return <AppLoading />;
  }

  return (
    <View style={styles.buttonBackground}>
      <TouchableOpacity style={styles.button} activeOpacity={0.5} onPress={() => handlerClick()}>
        <Text style={styles.text}>
          {toggleCabinet.getValue("cabinetOn") ? text : altText}
        </Text>
        
      </TouchableOpacity>
    </View>
  );
};

// Styles for the button and its container
const styles = StyleSheet.create({
  buttonBackground: {
    justifyContent: "center",
    alignItems: "center",
    backgroundColor: colors.ZF_Gray_100,
    width: "70%",
    height: "100%",
    borderRadius: 20,
  },
  button: {
    justifyContent: "center",
    alignItems: "center",
    backgroundColor: colors.ZF_Gray_100,
    borderColor: colors.ZF_Blue,
    borderWidth: 8,
    width: "100%",
    height: "100%",
    borderRadius: 20,
  },
  text: {
    fontFamily: "CustomFont",
    fontSize: 30,
    color: "#000", 
  },
});

export default BigButton;
