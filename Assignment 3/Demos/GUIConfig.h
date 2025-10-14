RUN_TESTS_MENU_OPTION()

WINDOW_TITLE("A Visit to Recursia")

MENU_ORDER("FlagGUI.cpp", "MountainGUI.cpp", "WordGUI.cpp", "TempleGUI.cpp", "CompositeGUI.cpp")

TEST_BARRIER("WordGUI.cpp", "SpeakingRecursian.cpp")
TEST_BARRIER("CompositeGUI.cpp", "MountainsOfRecursia.cpp", "TempleOfRecursia.cpp")
