# IMDb-TSV-Converter

Simple C program to convert IMDb's TSV datasets to CSVs compatible &amp; importable with my own database design.

## Documentation

### IMDb Data Converter Algorithm

1. Get id number
    -Retrieve tconst, drop first two characters "tt", and convert string to int w/ stoi()
2. Get title
3. Get startYear
    -Retrieve string and convert to int w/ stoi()
4. Get runtimeMinutes
5. Get genres (CSV)
