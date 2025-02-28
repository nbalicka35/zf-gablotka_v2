import { View, Text, StyleSheet, Button } from "react-native";

export default function HomeScreen({ navigation }) {
    return (
        <View style={styles.container}>
            <Text style={styles.text}>Welcome Screen</Text>
            <Button title='Go to blank' onPress={() => navigation.navigate("Blank")}/>
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