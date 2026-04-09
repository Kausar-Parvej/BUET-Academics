function app() {
  return {
    /* This is the main app object containing all the application state and methods. */
    // The following properties are used to store the state of the application

    // results of cache latency measurements
    latencyResults: null,
    // local collection of trace data
    traceData: [],
    // Local collection of heapmap images
    heatmaps: [],

    // Current status message
    status: "",
    // Is any worker running?
    isCollecting: false,
    // Is the status message an error?
    statusIsError: false,
    // Show trace data in the UI?
    showingTraces: false,

    // Collect latency data using warmup.js worker
    async collectLatencyData() {
      this.isCollecting = true;
      this.status = "Collecting latency data...";
      this.latencyResults = null;
      this.statusIsError = false;
      this.showingTraces = false;

      try {
        // Create a worker
        let worker = new Worker("warmup.js");

        // Start the measurement and wait for result
        const results = await new Promise((resolve) => {
          worker.onmessage = (e) => resolve(e.data);
          worker.postMessage("start");
        });

        // Update results
        this.latencyResults = results;
        this.status = "Latency data collection complete!";

        // Terminate worker
        worker.terminate();
      } catch (error) {
        console.error("Error collecting latency data:", error);
        this.status = `Error: ${error.message}`;
        this.statusIsError = true;
      } finally {
        this.isCollecting = false;
      }
    },

    // Collect trace data using worker.js and send to backend
    async collectTraceData() {
       /* 
        * Implement this function to collect trace data.
        * 1. Create a worker to run the sweep function.
        * 2. Collect the trace data from the worker.
        * 3. Send the trace data to the backend for temporary storage and heatmap generation.
        * 4. Fetch the heatmap from the backend and add it to the local collection.
        * 5. Handle errors and update the status.
        */
        this.isCollecting = true;
        this.status = "Collecting trace data...";
        this.statusIsError = false;
        this.showingTraces = true;

        try {
          const worker = new Worker("worker.js");
          const sweepData = await new Promise((resolve) => {
            worker.onmessage = (e) => resolve(e.data);
            worker.postMessage("start");
          });

          const response = await fetch("/collect_trace", {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({data: sweepData}),
          });

          if(!response.ok) throw new Error("Failed to collect trace.");

          const {heatmap_url} = await response.json();
          this.heatmaps.push(heatmap_url);
          this.status = "Trace data collection complete!";

        }catch (error) {
          console.error(error);
          this.status = `Error: ${error.message}`;
          this.statusIsError = true;

        }finally {
          this.isCollecting = false;
        }
    },

    // Download the trace data as JSON (array of arrays format for ML)
    async downloadTraces() {
       /* 
        * Implement this function to download the trace data.
        * 1. Fetch the latest data from the backend API.
        * 2. Create a download file with the trace data in JSON format.
        * 3. Handle errors and update the status.
        */

        this.status = "Downloading traces...";
        this.statusIsError = false;

        try {
          const response = await fetch("/api/trace_data");
          const traces = await response.json();

          const blob = new Blob([JSON.stringify(traces, null, 2)], {
            type: "application/json",
          });
          const url = URL.createObjectURL(blob);

          const link = document.createElement("a");
          link.href = url;
          link.download = "traces.json";
          link.click();

          URL.revokeObjectURL(url);
          this.status = "Download complete.";
        } catch (err) {
          console.error(err);
          this.status = `Error: ${err.message}`;
          this.statusIsError = true;
        }
    },

    // Clear all results from the server
    async clearResults() {
      /* 
       * Implement this function to clear all results from the server.
       * 1. Send a request to the backend API to clear all results.
       * 2. Clear local copies of trace data and heatmaps.
       * 3. Handle errors and update the status.
       */

      this.status = "Clearing results...";
      this.statusIsError = false;

      try {
        const res = await fetch("/api/clear_results", { method: "POST" });
        const result = await res.json();

        if (result.status !== "success") throw new Error(result.message);

        this.traceData = [];
        this.heatmaps = [];
        this.status = "Results cleared.";
      } catch (err) {
        console.error(err);
        this.status = `Error: ${err.message}`;
        this.statusIsError = true;
      }

    },
  };
}
