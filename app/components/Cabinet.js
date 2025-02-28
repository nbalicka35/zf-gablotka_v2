import React, { useState, useEffect } from "react";
import { View, StyleSheet, TouchableOpacity } from "react-native";
import colors from "../constants/colors";
import toggleCabinet from "../toggleObjects/ToggleCabinet";

/**
 * Cabinet component representing a grid of toggleable sectors.
 * 
 * This component renders a 2-column layout of cabinet sectors that can be toggled 
 * on or off if the cabinet itself is powered on and unlocked. It updates automatically 
 * every 100ms to reflect state changes.
 * 
 * Features:
 * - Uses `toggleCabinet` singleton to manage state.
 * - Updates every 100ms via `setInterval` to reflect external changes.
 * - Prevents toggling if the cabinet is locked.
 * 
 * @returns {JSX.Element} A view with interactive sectors.
 */
const Cabinet = () => {
  // State to force re-render when toggle states change
  const [updateTrigger, setUpdateTrigger] = useState(false);

  /**
   * Effect that triggers a re-render every 100ms.
   * Ensures that UI reflects changes in `toggleCabinet`.
   */
  useEffect(() => {
    const interval = setInterval(() => {
      setUpdateTrigger(prev => !prev); // This will trigger a re-render
    }, 100);

    return () => clearInterval(interval); // Cleanup on unmount
  }, []);

  /**
   * Handles button press to toggle a sector.
   * - Prevents toggling if the cabinet is locked.
   * - Updates the state in `toggleCabinet`.
   * - Triggers a re-render to reflect the new state.
   * 
   * @param {Object} param0 
   * @param {string} param0.button - The sector name to toggle.
   */
  const handlerClick = ({ button }) => {
    if (!toggleCabinet.getValue('isLocked')) {
      toggleCabinet.swapValue(button);
    }
    setUpdateTrigger(prev => !prev); // Force update after toggle
  };


  return (
    <View style={styles.container}>
      <View style={styles.column}>
        <TouchableOpacity style={toggleCabinet.getValue("cabinetOn") ? (toggleCabinet.getValue("sectorOneOn") ? styles.sectorOn : styles.sectorOff) : styles.sectorOff} 
          onPress={() => handlerClick({ button: "sectorOneOn"})} />

        <TouchableOpacity style={toggleCabinet.getValue("cabinetOn") ? (toggleCabinet.getValue("sectorThreeOn") ? styles.sectorOn : styles.sectorOff) : styles.sectorOff}
          onPress={() => handlerClick({ button: "sectorThreeOn"})} />

        <TouchableOpacity style={toggleCabinet.getValue("cabinetOn") ? (toggleCabinet.getValue("sectorFiveOn") ? styles.sectorOn : styles.sectorOff) : styles.sectorOff}
          onPress={() => handlerClick({ button: "sectorFiveOn"})} />

        <TouchableOpacity style={toggleCabinet.getValue("cabinetOn") ? (toggleCabinet.getValue("sectorSevenOn") ? styles.sectorOn : styles.sectorOff) : styles.sectorOff}
          onPress={() => handlerClick({ button: "sectorSevenOn"})} />
      </View>

      <View style={styles.column}>
        <TouchableOpacity style={toggleCabinet.getValue("cabinetOn") ? (toggleCabinet.getValue("sectorTwoOn") ? styles.sectorOn : styles.sectorOff) : styles.sectorOff} 
          onPress={() => handlerClick({ button: "sectorTwoOn"})} />

        <TouchableOpacity style={toggleCabinet.getValue("cabinetOn") ? (toggleCabinet.getValue("sectorFourOn") ? styles.sectorOn : styles.sectorOff) : styles.sectorOff}
          onPress={() => handlerClick({ button: "sectorFourOn"})} />

        <TouchableOpacity style={toggleCabinet.getValue("cabinetOn") ? (toggleCabinet.getValue("sectorSixOn") ? styles.sectorOn : styles.sectorOff) : styles.sectorOff}
          onPress={() => handlerClick({ button: "sectorSixOn"})} />

        <TouchableOpacity style={toggleCabinet.getValue("cabinetOn") ? (toggleCabinet.getValue("sectorEightOn") ? styles.sectorOn : styles.sectorOff) : styles.sectorOff}
          onPress={() => handlerClick({ button: "sectorEightOn"})} />
      </View>
    </View>
  );
};

// Styles for the cabinet layout and sectors
const styles = StyleSheet.create({
  container: {
    flexDirection: 'row',
    justifyContent: 'space-evenly', 
    alignItems: 'center', 
    padding: 10,
    backgroundColor: colors.ZF_Gray_800,
    width: '90%',
    height: '90%',
    flexWrap: 'wrap',
  },
  column: {
    justifyContent: 'space-evenly',
    alignItems: 'center',
    height: '100%',
    width: '48%',
  },
  sectorOn: {
    backgroundColor: colors.ZF_Cyan,
    width: '100%',
    height: '24%',
  },
  sectorOff: {
    backgroundColor: colors.ZF_Dark_Blue,
    width: '100%',
    height: '24%',
  }
});

export default Cabinet;
