const { readFileSync, writeFileSync } = require('fs');
const path = require('path');

const includedFiles = new Set(); // To track included files and prevent circular dependencies
const angleBracketIncludes = new Set(); // To store angle bracket includes
let fileContent = ""; // To store combined content

const srcDir = path.join(__dirname, 'src');

// Function to process a single file
function processFile(filePath) {
  const content = readFileSync(filePath, 'utf-8');
  const lines = content.split('\n');
  
  for (const line of lines) {
    const includeMatch = line.match(/#include\s+["<](.+)[">]/);
    
    if (includeMatch) {
      const includedFile = includeMatch[1];
      const fullPath = path.join(srcDir, includedFile);

      if (line.startsWith('#include <')) {
        // Collect angle bracket includes to add them at the top
        if (!angleBracketIncludes.has(includedFile)) {
          angleBracketIncludes.add(includedFile);
        }
      } else if (line.startsWith('#include "')) {
        // Process quoted includes by reading their content
        if (!includedFiles.has(fullPath)) {
          includedFiles.add(fullPath);
          try {
            processFile(fullPath);
          } catch (error) {
            console.error(`Error processing file ${fullPath}: ${error.message}`);
          }
        }
      }
    } else {
      fileContent += line + '\n';
    }
  }
}

// Function to combine multiple files into one
function combine(files, outputFileName) {
  includedFiles.clear();
  angleBracketIncludes.clear();
  fileContent = "";

  let isHeaderFile = outputFileName.endsWith('.h');

  if (isHeaderFile) {
    // Add include guard for header files
    const guardMacro = outputFileName.replace(/[^\w]/g, '_').toUpperCase();
    fileContent += `#ifndef ${guardMacro}\n#define ${guardMacro}\n\n`;
  }

  // Process each file
  files.forEach(file => {
    const filePath = path.join(srcDir, file);
    if (!includedFiles.has(filePath)) {
      includedFiles.add(filePath);
      processFile(filePath);
    }
  });

  // Add angle bracket includes at the top
  angleBracketIncludes.forEach(inc => {
    fileContent = `#include <${inc}>\n` + fileContent;
  });

  if (isHeaderFile) {
    // End include guard for header files
    const guardMacro = outputFileName.replace(/[^\w]/g, '_').toUpperCase();
    fileContent += `\n#endif // ${guardMacro}\n`;
  }

  // Write to the output file
  const outputPath = path.join(__dirname, outputFileName);
  writeFileSync(outputPath, fileContent, 'utf-8');
  console.log(`${outputFileName} has been created successfully.`);
}

// Example usage
combine(["vec.h", "zstd.h", "draw.h", "keyboard.h", "object.h", "colors.h"], 'zstd.h');
combine(["zstd.cpp", "draw.cpp", "keyboard.cpp"], 'zstd.cpp');
