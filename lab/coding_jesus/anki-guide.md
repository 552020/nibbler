# Guide: Converting Markdown Q/A to Anki Cards

This guide shows you how to convert your C++ interview questions from Markdown format into Anki flashcards.

---

## Markdown Format

Structure your questions and answers in a simple format:

```markdown
Q: What is a shared_ptr?

A: A reference-counted smart pointer with shared ownership. Multiple shared_ptr instances can point to the same object, and the object is automatically deleted when the last shared_ptr is destroyed.

Q: What is the difference between unique_ptr, shared_ptr, and weak_ptr?

A: 
- unique_ptr: Exclusive ownership, cannot be copied, only moved
- shared_ptr: Shared ownership with reference counting
- weak_ptr: Non-owning observer, doesn't affect reference count, used to break cycles

Q: What is the size of a shared_ptr?

A: Typically 16 bytes on 64-bit systems (8 bytes for the pointer, 8 bytes for the control block pointer).
```

**Key points:**
- Each question starts with `Q:`
- Each answer starts with `A:`
- Questions and answers can span multiple lines
- Empty lines between Q/A pairs are optional but recommended

---

## Option A: Generate .apkg File (Recommended)

This method creates an Anki package file that you can import directly.

### Setup

1. Install the required Python library:
```bash
pip install genanki
# Or using requirements.txt:
pip install -r requirements.txt
```

2. Use the provided script `build_anki_deck.py`

### Usage

1. Create a markdown file with Q/A format (e.g., `cpp_questions.md`)
2. Run the script:
```bash
python build_anki_deck.py cpp_questions.md
```

3. This generates `cpp_interview.apkg`
4. Open Anki → File → Import → Select `cpp_interview.apkg`
5. Done! Your cards are now in Anki

### Advantages
- No need to have Anki running
- Creates a portable `.apkg` file
- Can be shared with others
- Works offline

---

## Option B: Direct Import via AnkiConnect

This method pushes cards directly into a running Anki instance.

### Setup

1. Install AnkiConnect addon in Anki:
   - Tools → Add-ons → Get Add-ons
   - Code: `2055492159`
   - Restart Anki

2. Keep Anki open while running the script

3. Use the provided script `build_anki_connect.py`

### Usage

1. Make sure Anki is running
2. Create a markdown file with Q/A format
3. Run the script:
```bash
python build_anki_connect.py cpp_questions.md
```

4. Cards are automatically added to your Anki deck

### Advantages
- Instant import, no manual step
- Can add tags automatically
- Good for incremental updates

### Disadvantages
- Requires Anki to be running
- Requires AnkiConnect addon

---

## Workflow Recommendation

**For initial setup:**
- Use Option A (genanki) to create the deck from scratch
- Import the `.apkg` file into Anki

**For adding new questions:**
- Add Q/A pairs to your markdown file
- Regenerate the `.apkg` file
- Import again (Anki will handle duplicates if configured)

**Alternative workflow:**
- Use Option B (AnkiConnect) for quick additions
- Use Option A for full deck regeneration

---

## Tips

1. **Keep your markdown as source of truth** - maintain one master markdown file
2. **Use tags** - the scripts support adding tags to cards (e.g., "cpp", "smart-pointers")
3. **Format answers well** - use markdown formatting in answers (the scripts preserve it)
4. **Test with a small file first** - create a test markdown with 2-3 questions to verify the format works

---

## Troubleshooting

**Problem:** Script can't parse questions
- **Solution:** Make sure each question starts with `Q:` and answer with `A:` on separate lines

**Problem:** AnkiConnect not working
- **Solution:** Check that Anki is running and AnkiConnect addon is installed and enabled

**Problem:** Cards not showing up
- **Solution:** Check the deck name in Anki matches what the script uses (default: "C++ Interview")

---

## Example Markdown File Structure

See `cpp_questions_example.md` for a complete example of the Q/A format.

