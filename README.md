# 🗄️ CSV Manager in C

A simple command-line **CSV Manager** written in C that allows users to load, view, add, update, delete, sort, search, and save records in a CSV file. Ideal for lightweight data manipulation without requiring full database software. 📋

---

## ✨ Features ✨

* **Load CSV**: Reads headers and rows from a specified CSV file. 📂
* **Display Data**: Prints the full table with neatly aligned columns. 🖨️
* **Add Record**: Append a new row by entering values for each column. ➕
* **Update Record**: Modify an existing cell by specifying column and row. ✏️
* **Delete Record**: Remove a row by its index. ❌
* **Sort Data**: Sort rows ascending or descending by a chosen column. 🔀
* **Search Data**: Find and display records matching a specific column value. 🔍
* **Save Changes**: Write current data back to the original CSV file. 💾
* **Unsaved Changes Warning**: Prompt to save before exiting. ⚠️

---

## 🛠️ Tech Stack & Dependencies 🛠️

* **Language**: C (C99 or later)
* **Standard Library**: `stdio.h`, `string.h`, `ctype.h`

---

## 📥 Installation & Compilation 📥

1. **Clone the repository**:

   ```bash
   git clone https://github.com/yourusername/csv-manager-c.git
   cd csv-manager-c
   ```

2. **Compile the code**:

   ```bash
   gcc -std=c99 -o csv_manager main.c
   ```

3. **Run the program**:

   ```bash
   ./csv_manager
   ```

---

## 🚀 Usage 🚀

1. **Enter CSV filename** when prompted (e.g., `data.csv`).
2. **Interact with menu**:

   1. Add a record
   2. Update a record
   3. Delete a record
   4. Sort data by column
   5. Search data
   6. Save data
   7. Exit
3. **Follow on-screen prompts** to enter column names, row numbers, sort order, or search values.
4. **Save before exit** to persist changes back to the CSV file.

---

## 📁 Project Structure 📁

```
├── main.c           # Source code for CSV manager
├── data.csv         # Example CSV file (optional)
└── README.md        # Project documentation
```

---

## 🎨 Customization 🎨

* **Max Rows/Columns**: Adjust `MAX_ROWS` and `MAX_COLUMNS` in `main.c` for larger datasets.
* **String Lengths**: Modify `MAX_STRING_LENGTH` or `MAX_LINE_LENGTH` for longer fields or lines.
* **Delimiter**: Change `strtok` delimiter in code to support different separators (e.g., `;`).

---

## 🐞 Troubleshooting 🐞

* **File Not Found**: Ensure the CSV file exists in the working directory and the name is correct. 🔗
* **Partial Reads**: Check for lines exceeding `MAX_LINE_LENGTH`. Increase buffer if needed. 📏
* **Unsaved Data**: Always choose option 6 to save before exiting to avoid data loss. 💾

---

## 📄 License 📄

This project is licensed under the MIT License. See `LICENSE` for details. 📜

---

## 🤝 Contributing 🤝

Contributions are welcome!:

* 🐛 Report issues or bugs
* ✨ Suggest new features or improvements
* 🔀 Submit pull requests

Enjoy managing your CSV data! 🚀
