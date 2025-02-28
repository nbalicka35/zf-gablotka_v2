import { View, StyleSheet, Dimensions, StatusBar } from "react-native";
import colors from "../constants/colors";
const { width } = Dimensions.get("window");


/**
 * Configuration for background circles
 * @typedef {Object} Circle
 * @property {number} size - Diameter of the circle as a percentage of the screen width
 * @property {string} color - Color of the circle (using predefined colors)
 * @property {string} top - Distance from the top of the parent container (percentage)
 * @property {string} left - Distance from the left of the parent container (percentage)
 */
/** @type {Circle[]} */
const circles = [
  { size: 0.45, color: colors.ZF_Orange_25, top: "1%", left: "-30%" },
  { size: 0.45, color: colors.ZF_Orange_50, top: "-11%", left: "-7%" },
  { size: 0.08, color: colors.ZF_Orange_25, top: "14%", left: "24%" },
  { size: 0.7, color: colors.ZF_Purple_50, top: "5%", left: "82%" },
  { size: 0.6, color: colors.ZF_Purple_50, top: "82%", left: "-30%" },
  { size: 0.1, color: colors.ZF_Purple_25, top: "80%", left: "25%" },
  { size: 0.4, color: colors.ZF_Orange_25, top: "75%", left: "85%" },
  { size: 0.6, color: colors.ZF_Orange_50, top: "84%", left: "68%" },
];

/**
 * Background component that renders decorative circles in absolute positions.
 * 
 * This component creates a set of circles positioned on the screen to serve as a background.
 * The circles are defined in the `circles` array, specifying their size, color, and position.
 * 
 * Features:
 * - Uses `StatusBar` for a translucent effect.
 * - Dynamically calculates circle sizes based on screen width.
 * - Uses absolute positioning to freely place circles in the background.
 * 
 * @returns {JSX.Element} The background view with styled circles.
 */
const Background = () => {
  return (
    <View style={styles.container}>
      <StatusBar translucent backgroundColor="transparent" barStyle="dark-content" />
      
      {/* Background Circles */}
      {circles.map((circle, index) => (
        <View
          key={index}
          style={[
            styles.circle,
            {
              width: width * circle.size,
              height: width * circle.size,
              borderRadius: (width * circle.size) / 2,
              backgroundColor: circle.color,
              top: circle.top,
              left: circle.left,
            },
          ]}
        />
      ))}

    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    ...StyleSheet.absoluteFillObject,
    justifyContent: "center",
    alignItems: "center",
  },
  circle: {
    position: "absolute",
  },
});

export default Background;
