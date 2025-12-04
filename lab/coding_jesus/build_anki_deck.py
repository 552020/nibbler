#!/usr/bin/env python3
"""
Convert Markdown Q/A format to Anki .apkg file using genanki.

Usage:
    python build_anki_deck.py input.md [output.apkg] [deck_name]

Example:
    python build_anki_deck.py cpp_questions.md
    python build_anki_deck.py cpp_questions.md my_deck.apkg "My C++ Deck"
"""

import genanki
import re
import sys
from pathlib import Path


def parse_markdown_qa(md_text):
    """
    Parse markdown text with Q: and A: format.
    Reads from Q: to A: to ___ separator.
    Skips section titles (## headers).
    Returns list of (question, answer) tuples.
    """
    pairs = []
    lines = md_text.split('\n')
    i = 0
    
    while i < len(lines):
        line = lines[i].strip()
        
        # Skip section headers (## or ###)
        if re.match(r'^#{2,3}\s+', line):
            i += 1
            continue
        
        # Look for Q: marker
        if line.startswith('Q:'):
            question = line[2:].strip()
            i += 1
            
            # Collect multi-line question until we hit A:
            while i < len(lines):
                if lines[i].strip().startswith('A:'):
                    break
                # Skip section headers
                if re.match(r'^#{2,3}\s+', lines[i].strip()):
                    i += 1
                    continue
                question += '\n' + lines[i]
                i += 1
            
            # Now look for A:
            if i < len(lines) and lines[i].strip().startswith('A:'):
                answer = lines[i].strip()[2:].strip()
                i += 1
                
                # Collect multi-line answer until we hit ___ or next Q:
                while i < len(lines):
                    line_stripped = lines[i].strip()
                    # Stop at ___ separator
                    if line_stripped == '___':
                        i += 1
                        break
                    # Stop at next Q:
                    if line_stripped.startswith('Q:'):
                        break
                    # Skip section headers
                    if re.match(r'^#{2,3}\s+', line_stripped):
                        i += 1
                        continue
                    answer += '\n' + lines[i]
                    i += 1
                
                if question.strip() and answer.strip():
                    pairs.append((question.strip(), answer.strip()))
                continue
        
        i += 1
    
    return pairs


def create_anki_deck(md_file, output_file=None, deck_name=None):
    """
    Create an Anki deck from a markdown file.
    """
    md_path = Path(md_file)
    if not md_path.exists():
        print(f"Error: File {md_file} not found")
        return False
    
    # Read markdown file
    md_text = md_path.read_text(encoding='utf-8')
    
    # Parse Q/A pairs
    pairs = parse_markdown_qa(md_text)
    
    if not pairs:
        print("Error: No Q/A pairs found in the markdown file")
        print("Make sure your format is:")
        print("Q: Your question here")
        print("A: Your answer here")
        return False
    
    print(f"Found {len(pairs)} Q/A pairs")
    
    # Generate unique IDs (using hash of deck name or file name)
    deck_id = hash(md_path.name) % (10**10)
    model_id = hash("C++ Q/A Model") % (10**10)
    
    # Create deck
    deck = genanki.Deck(
        deck_id,
        deck_name or "C++ Interview Questions"
    )
    
    # Create note model (Basic Q/A)
    model = genanki.Model(
        model_id,
        "C++ Q/A",
        fields=[
            {"name": "Question"},
            {"name": "Answer"},
        ],
        templates=[
            {
                "name": "Card 1",
                "qfmt": "{{Question}}",
                "afmt": "{{FrontSide}}<hr id=answer>{{Answer}}",
            },
        ],
        css="""
        .card {
            font-family: arial;
            font-size: 20px;
            text-align: left;
            color: black;
            background-color: white;
        }
        .card code {
            background-color: #f4f4f4;
            padding: 2px 4px;
            border-radius: 3px;
            font-family: 'Courier New', monospace;
        }
        """
    )
    
    # Add notes
    for i, (question, answer) in enumerate(pairs, 1):
        # Clean up whitespace
        question = question.strip()
        answer = answer.strip()
        
        if not question or not answer:
            print(f"Warning: Skipping pair {i} (empty question or answer)")
            continue
        
        note = genanki.Note(
            model=model,
            fields=[question, answer],
            tags=["cpp", "interview"]
        )
        deck.add_note(note)
    
    # Generate package
    output_path = output_file or md_path.with_suffix('.apkg')
    package = genanki.Package(deck)
    package.write_to_file(str(output_path))
    
    print(f"Successfully created {output_path}")
    print(f"Import this file into Anki: File → Import → {output_path}")
    
    return True


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    
    md_file = sys.argv[1]
    output_file = sys.argv[2] if len(sys.argv) > 2 else None
    deck_name = sys.argv[3] if len(sys.argv) > 3 else None
    
    success = create_anki_deck(md_file, output_file, deck_name)
    sys.exit(0 if success else 1)

