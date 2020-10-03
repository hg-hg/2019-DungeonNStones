// If all goes well prints JSON to stdout

const fs = require('fs');
const readline = require('readline');
const path = process.argv[process.argv.length-1];

let data = {};
var rl = readline.createInterface({
  input : fs.createReadStream(path),
  output: process.stdout,
  terminal: false,
});
rl
.on('line', (line) => {
  let m = line.match(/([a-z_]+) +([0-9]+) +([0-9]+) +([0-9]+) +([0-9]+) ?([0-9]?)/);
  if(m){
    data[m[1]] = {
      x: parseInt(m[2]),
      y: parseInt(m[3]),
      w: parseInt(m[4]),
      h: parseInt(m[5]),
      animLen: parseInt(m[6] || 1),
      isAnim: !!m[6],
    };
  }
})
.on('close', () => {
  console.log(JSON.stringify(data, null, 4));
});

