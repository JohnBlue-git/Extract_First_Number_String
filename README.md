
### Comparison remark:
- find_first_of()/find_first_not_of():
  - it will likely perform better (i.e., faster) for simple tasks like extracting the first number, especially when processing large volumes of strings.
- Regex
  - it will be slower due to pattern compilation and matching overhead, but it's more powerful when you need complex matching logic.
