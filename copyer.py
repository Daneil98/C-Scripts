import os
from pathlib import Path

def append_txt_contents(source_dir, target_dir):
    """
    Copies contents from .txt files in source_dir and appends them to
    corresponding .txt files in target_dir.
    
    Args:
        source_dir (str): Path to source directory with original .txt files
        target_dir (str): Path to target directory where contents will be appended
    """
    source_path = Path(source_dir)
    target_path = Path(target_dir)
    
    # Create target directory if it doesn't exist
    target_path.mkdir(parents=True, exist_ok=True)
    
    # Process each .txt file in source directory
    for src_file in source_path.glob('*.txt'):
        # Get corresponding target file path
        tgt_file = target_path / src_file.name
        
        # Read source file contents
        with open(src_file, 'r') as f:
            src_content = f.read().strip()  # Remove any trailing whitespace
            
        if not src_content:  # Skip if source file is empty
            continue
            
        # Prepare content to append (with newline if target file exists)
        if tgt_file.exists():
            with open(tgt_file, 'r+') as f:
                existing_content = f.read()
                # Only add newline if file isn't empty
                append_content = f"\n{src_content}" if existing_content else src_content
                f.write(append_content)
        else:
            # Create new file with the content
            with open(tgt_file, 'w') as f:
                f.write(src_content)
                
        print(f"Appended contents from {src_file} to {tgt_file}")

# Example usage
source_directory = "C:/Users/samsung/Videos/face"
target_directory = "C:/Users/samsung/Videos/Final - Copy/labels/val"


append_txt_contents(source_directory, target_directory)