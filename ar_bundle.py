#!/usr/bin/env python

import sys
import os

def get_content(full_path):
  with open(full_path) as fin:
    return fin.read()

def run(input_directory):
  if not os.path.isdir(input_directory):
    print("Error: Directory not found:", input_directory)
    return

  hpp_template = get_content("lib/web_server/static_web_files_template.hpp")

  web_static_files = {}
  for current_dir, directories, filenames in os.walk(input_directory):
    for filename in filenames:
      full_path = os.path.join(current_dir, filename)
      relative_path = os.path.relpath(full_path, input_directory)
      web_static_files[relative_path] = get_content(full_path)

  decl_lines = []
  page_lines = []
  for decl_id, (relative_path, content) in enumerate(web_static_files.items()):
    decl = decl_id
    decl_name = 'web_server_page_content_{}'.format(decl_id)
    decl_line = 'constexpr auto {} = R"WEB_SERVER({})WEB_SERVER";'.format(decl_name, content)
    page_line = '  {} "{}", {} {},'.format('{', relative_path, decl_name, "}")
    decl_lines.append(decl_line)
    page_lines.append(page_line)

  for page_line in page_lines:
    output_content = hpp_template.replace("WEB_SERVER_DECL_HOOKS", '\n'.join(decl_lines))
    output_content = output_content.replace("WEB_SERVER_PAGE_HOOKS", '\n'.join(page_lines))
    with open("lib/web_server/static_web_files.hpp", 'w+') as fout:
      fout.write(output_content)

def main():
  if len(sys.argv) != 2:
    print("Error: ./ar_bundle.py {directory}")
    return

  run(sys.argv[1])

if __name__ == '__main__':
  main()
