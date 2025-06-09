
dirs=()
for dir in $(ls -d exerc*/ | sort -V); do
    dirs+=("$dir")
done

# Check if any exercise directories were found
if [ ${#dirs[@]} -eq 0 ]; then
    echo "Error: No 'exerc' directories found in the current folder."
    echo "Please make sure you are running this script from the root of the project."
    exit 1
fi

# --- Step 2: Display the menu of options to the user ---
echo ""
echo "=========================================="
echo "   Estrutura de Dados 2 - Main Menu   "
echo "=========================================="
echo ""
echo "Please choose a program to run (or press CTRL+C to exit):"

# 'select' is a bash feature that creates menus automatically
select choice in "${dirs[@]}"; do
    # Check if the user's input was a valid number from the list
    if [ -n "$choice" ]; then
        # Check if the corresponding run.sh script exists and is executable
        if [ -x "${choice}main.sh" ]; then
            echo ""
            echo "--- Running script in ${choice} ---"
echo ""
            
            # Change directory to the chosen folder and execute its run script
            (cd "$choice" && ./main.sh)
            
            echo ""
            echo "--- Script finished. Returning to menu. ---"
            echo "=========================================="
            # After running, break the loop and exit the script.
            # If you want the menu to re-appear, remove the 'break' line.
            break

        else
            echo "Error: '${choice}main.sh' not found or is not executable."
            echo "Please run 'chmod +x ${choice}main.sh' and try again."
            break
        fi
    else
        # This message appears if the user enters a number not on the list
        echo "Invalid option. Please enter a number from 1 to ${#dirs[@]}."
    fi
done

exit 0