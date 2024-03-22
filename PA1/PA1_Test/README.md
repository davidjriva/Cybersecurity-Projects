Running Command:    
    ./cipher B $(INPUT_FILE) $(INTERMEDIATE_FILE) $(BLOCK_KEY_FILE) E


Test Cases:
    E/B/1 -- No Difference
    E/B/2 -- Files Differ
    E/B/3 -- Files Differ

    D/B/1 -- No Difference
    D/B/2 -- Files Differ
    D/B/3 -- Files Differ