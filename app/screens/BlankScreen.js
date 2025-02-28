import { View, Text, StyleSheet, Button } from "react-native";

export default function BlankScreen({ navigation }) {
    return (
        <View style={styles.container}>
            <Text style={styles.text}>BlankScreen</Text>
            <Button title='Go to home' onPress={() => navigation.navigate("Home")}/>
            <Button title='Go to main' onPress={() => navigation.navigate("Main")}/>
        </View>
    )
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
});