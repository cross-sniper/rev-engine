import os, sys

included_headers = set()
header_content = ""

src_dir = os.path.join(os.path.dirname(__file__), "src")


def include_file(header_name):
    global header_content
    if header_name not in included_headers:
        included_headers.add(header_name)
        header_content += f"#include <{header_name}>\n"
        # Optional: Print debug message
        print(f'Included header "{header_name}"')
    else:
        # Optional: Print debug message
        print(f'"{header_name}" was already included')


def read_and_process_file(file, inclusion):
    global header_content
    file_path = os.path.join(src_dir, file)

    if file not in included_headers:
        included_headers.add(file)

        if os.path.isfile(file_path):
            with open(file_path, "r") as f:
                content = f.read()
                lines = content.splitlines()

                for line in lines:
                    if line.startswith("#include"):
                        include_parts = line.split(" ")
                        if len(include_parts) == 2:
                            included_file = include_parts[1].strip('"<>')
                            if line.startswith("#include <"):
                                include_file(included_file)
                            elif line.startswith('#include "'):
                                read_and_process_file(included_file, file)
                    else:
                        header_content += line + "\n"
            print(f'File "{file}" included by "{inclusion}"')
        else:
            print(f'File "{file}" required by "{inclusion}" not found')
            exit(1)


def combine_files(files, output_file_name):
    global header_content
    included_headers.clear()
    header_content = ""

    is_header_file = output_file_name.endswith(".h")
    guard_macro = output_file_name.replace(".", "_").upper()

    if is_header_file:
        header_content += f"#ifndef {guard_macro}\n#define {guard_macro}\n\n"

    for file in files:
        file_path = os.path.join(src_dir, file)
        if file_path not in included_headers:
            read_and_process_file(file, file_path)

    if is_header_file:
        header_content += f"\n#endif // {guard_macro}\n"

    output_path = os.path.join(os.path.dirname(__file__), output_file_name)
    with open(output_path, "w") as f:
        f.write(header_content)

    print(f"{output_file_name} has been created successfully.")


combine_files(
    [
        "vec.h",
        "zstd.h",
        "draw.h",
        "keyboard.h",
        "object.h",
        "colors.h",
        "mouse.h",
        "Image.h",
    ],
    "zstd.h",
)

combine_files(
    ["vec.cpp", "draw.cpp", "keyboard.cpp", "mouse.cpp", "Image.cpp","zstd.cpp"],
    "zstd.cpp",
)

if "-c" in sys.argv:
    print("compiling to .a")
    cmds = [
        "g++ zstd.cpp -c -o zstd.o " + "-D DEBUG_LOG_ENABLED" if "-d" in sys.argv else "",
        "ar rcs libzstd.a zstd.o",  # Create the static library
    ]

    for cmd in cmds:
        print(cmd)
        os.system(cmd)
