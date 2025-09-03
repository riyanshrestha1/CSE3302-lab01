# Name: Riyan Shrestha
# ID: 1002223799
# Language Version: Python 3.12.1
# OS: Ubuntu 24.04

import os
import sys

def calculate_size(path= str) -> int:

    total_size = 0
    
    try:
        # Get list of all items in the current directory
        items = os.listdir(path)
        
        # Iterate through each item in the directory
        for item in items:
            item_path = os.path.join(path, item)
            
            try:
                # Check if the item is a directory
                if os.path.isdir(item_path):
                    # Recursively call this function for subdirectories
                    total_size += calculate_size(item_path)
                elif os.path.isfile(item_path):
                    # Add the file size to the total
                    total_size += os.path.getsize(item_path)
            except (OSError, IOError):
                # Skip files/directories that cannot be accessed due to permissions
                continue
                
    except (OSError, IOError):
        # Handle case where directory cannot be accessed
        return 0
    
    return total_size
# Entry point of the program
if __name__ == "__main__":
    start_path = sys.argv[1] if len(sys.argv) > 1 else "."
    size_bytes = calculate_size(start_path)
    print(size_bytes)