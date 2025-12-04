#!/usr/bin/env python3
"""
Convert Markdown Q/A format to Anki cards using AnkiConnect.

Requires:
    - Anki to be running
    - AnkiConnect addon installed (code: 2055492159)

Usage:
    python build_anki_connect.py input.md [deck_name]

Example:
    python build_anki_connect.py cpp_questions.md
    python build_anki_connect.py cpp_questions.md "My C++ Deck"
"""

import json
import urllib.request
import re
import sys
from pathlib import Path


def anki_request(action, **params):
    """
    Send a request to AnkiConnect.
    """
    request_json = json.dumps({
        "action": action,
        "version": 6,
        "params": params
    }).encode('utf-8')
    
    try:
        response = json.loads(urllib.request.urlopen(
            urllib.request.Request('http://localhost:8765', request_json)
        ).read().decode('utf-8'))
        
        if response.get('error'):
            raise Exception(f"AnkiConnect error: {response['error']}")
        
        return response.get('result')
    except urllib.request.URLError:
        raise Exception("Could not connect to Anki. Make sure Anki is running and AnkiConnect is installed.")


def parse_markdown_qa(md_text):
    """
    Parse markdown text with Q: and A: format.
    Returns list of (question, answer) tuples.
    """
    pairs = []
    parts = re.split(r'^Q:\s*', md_text, flags=re.MULTILINE)[1:]  # Skip first empty part
    
    for part in parts:
        if 'A:' in part:
            q, a = part.split('A:', 1)
            q = q.strip()
            a = a.strip()
            if q and a:
                pairs.append((q, a))
    
    return pairs


def check_anki_connect():
    """
    Check if AnkiConnect is available.
    """
    try:
        result = anki_request("version")
        print(f"Connected to AnkiConnect (version: {result})")
        return True
    except Exception as e:
        print(f"Error: {e}")
        return False


def create_anki_cards(md_file, deck_name=None):
    """
    Create Anki cards from a markdown file using AnkiConnect.
    """
    md_path = Path(md_file)
    if not md_path.exists():
        print(f"Error: File {md_file} not found")
        return False
    
    # Check AnkiConnect
    if not check_anki_connect():
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
    
    # Use provided deck name or default
    deck = deck_name or "C++ Interview Questions"
    
    # Ensure deck exists
    try:
        deck_names = anki_request("deckNames")
        if deck not in deck_names:
            anki_request("createDeck", deck=deck)
            print(f"Created deck: {deck}")
    except Exception as e:
        print(f"Warning: Could not create/verify deck: {e}")
    
    # Get model name (usually "Basic" or "Basic (and reversed card)")
    model_name = "Basic"
    
    # Add cards
    added = 0
    skipped = 0
    
    for i, (question, answer) in enumerate(pairs, 1):
        try:
            result = anki_request(
                "addNote",
                note={
                    "deckName": deck,
                    "modelName": model_name,
                    "fields": {
                        "Front": question,
                        "Back": answer,
                    },
                    "options": {
                        "allowDuplicate": False,
                    },
                    "tags": ["cpp", "interview"],
                }
            )
            
            if result:
                added += 1
                print(f"Added card {i}/{len(pairs)}: {question[:50]}...")
            else:
                skipped += 1
                print(f"Skipped card {i} (duplicate or error)")
                
        except Exception as e:
            print(f"Error adding card {i}: {e}")
            skipped += 1
    
    print(f"\nDone! Added {added} cards, skipped {skipped} cards")
    print(f"Deck: {deck}")
    
    return True


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    
    md_file = sys.argv[1]
    deck_name = sys.argv[2] if len(sys.argv) > 2 else None
    
    success = create_anki_cards(md_file, deck_name)
    sys.exit(0 if success else 1)


