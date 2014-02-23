var g_currentScreen = "Main"

function hideScreen(screen) {
    if (screen === "History")
        hideHistory();
}

function showScreen(screen) {
    hideScreen(g_currentScreen);
    if (screen === "History")
        showHistory();
}

function showHistory() {
    g_currentScreen = "History"
    historyScreen.state = "Shown";
}

function hideHistory() {
    historyScreen.state = "Hidden";
}
