# write_to_new_file_without_comments — Compact Version

### Goal:
Detect and skip single-line comments (`//`) more compactly, using minimal variables.

---

### Code Snippet

```c
void write_to_new_file_without_comments(FILE* fileReadPtr, FILE* fileWritePtr){
    int character;
    bool matchFound = false;
    bool commentDelimiterFound = false;

    while ((character = fgetc(fileReadPtr)) != EOF) {

        if(character == '/'){
            if(character == '/' && matchFound == true){
                commentDelimiterFound = true;
            }
            matchFound = true;
        }else{
            if(matchFound == true && commentDelimiterFound == false){
                fputc('/', fileWritePtr);
            }
            matchFound = false;

            if(commentDelimiterFound == true && character != '\n'){
                continue;
            }else{
                commentDelimiterFound = false;
            }

            fputc(character, fileWritePtr);
        }
    }
}
```

## Rationale
* **When `/` is found:**
    * The first `/` sets `matchFound = true`.
    * If the next character is another `/`, both conditions (`character == '/' && matchFound == true`) become true, and `commentDelimiterFound` is set to `true`.

* **When the next character is not `/`:**
    * Control moves to the `else` block, where the function writes a single `/` manually (because `/` wasn’t printed earlier).
    * `matchFound` is reset to `false`.

* **If `commentDelimiterFound` is true:**
    * The program continues skipping characters until it reaches a newline `\n`, meaning the comment has ended.

## Why i'm not using it in main project file
Although it produces the same output:

* It’s **less readable**.
* It provides **no performance improvement**.
* Debugging or modifying logic later would be harder for future me.


## Status
* **Functionally correct**
* **Not used in main project** — kept here for reference
