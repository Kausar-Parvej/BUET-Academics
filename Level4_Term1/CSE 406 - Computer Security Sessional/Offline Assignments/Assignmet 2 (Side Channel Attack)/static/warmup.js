/* Find the cache line size by running `getconf -a | grep CACHE` */
const LINESIZE = 64;

function readNlines(n) {
  /*
   * Implement this function to read n cache lines.
   * 1. Allocate a buffer of size n * LINESIZE.
   * 2. Read each cache line (read the buffer in steps of LINESIZE) 10 times.
   * 3. Collect total time taken in an array using `performance.now()`.
   * 4. Return the median of the time taken in milliseconds.
   */

  const bufferSize = n * LINESIZE;
  const buffer = new Uint8Array(bufferSize);
  const times = [];
  const iterations = 10;

  for (let trial=0; trial<iterations; trial++){
    const start = performance.now();
    //console.log(start);

    for (let i=0; i<bufferSize; i+=LINESIZE){
      buffer[i]; // Accessing one byte per cache line
    }

    const end = performance.now();
    times.push(end - start);
  }

  times.sort((a, b) => a - b);  //The comparator (a, b) => a - b ensures numerical sorting
  const mid = Math.floor(times.length / 2);
  //console.log(`Time taken = ${times[mid]} ms`);
  if(times.length%2 == 0) return (times[mid - 1] + times[mid]) / 2; // Average of two middle values
  return times[mid];
}



self.addEventListener("message", function (e) {
  if (e.data === "start") {
    const results = {};

    /* Call the readNlines function for n = 1, 10, ... 10,000,000 and store the result */

    const maxN = 10000000;
    for (let n=1; n<=maxN; n*=10){
      try{
        const latency = readNlines(n);
        results[n] = latency;
      }
      catch (error) {
        console.error(`Error reading ${n} lines:`, error);
        break;
      }
    }

    self.postMessage(results);
  }
});
