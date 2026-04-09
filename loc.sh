cd src 
find -type f \( -name '*.cpp' -o -name '*.h' \) | xargs wc -l {}
