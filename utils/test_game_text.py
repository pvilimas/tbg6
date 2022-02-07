import re, sys

"""
use this script to see how text will look displayed in the game to make sure it isn't cut off
"""

LINECOUNT = 4
LINELENGTH = 60

regex = fr"(.{{1,{LINELENGTH}}})(?:(\s)+|$)"

def get_shown_text(text: str) -> str:
    return re.findall(regex, text, re.IGNORECASE)

test_str = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."

print()
l = [''.join(x).strip() for x in get_shown_text(test_str)][:4]
print(f'This text will be shown ({LINELENGTH}x{LINECOUNT}):\n')
print('\n'.join(l))
print()
