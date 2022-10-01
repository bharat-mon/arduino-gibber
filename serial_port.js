class LineBreakTransformer {
  constructor() {
    // A container for holding stream data until a new line.
    this.chunks = "";
  }

  transform(chunk, controller) {
    // Append new chunks to existing chunks.
    this.chunks += chunk;
    // For each line breaks in chunks, send the parsed lines out.
    const lines = this.chunks.split("\r\n");
    this.chunks = lines.pop();
    lines.forEach((line) => controller.enqueue(line));
  }

  flush(controller) {
    // When the stream is closed, flush any remaining chunks out.
    controller.enqueue(this.chunks);
  }
}

doserial = async function () {
  window.port = await navigator.serial.requestPort();
  await port.open({ baudRate: 9600 });
  const textDecoder = new TextDecoderStream();
  port.readable.pipeTo(textDecoder.writable);
  window.reader = textDecoder.readable
    .pipeThrough(new TransformStream(new LineBreakTransformer()))
    .getReader();

  while (port.readable) {
    try {
      while (true) {
        const { value, done } = await reader.read();
        if (done) {
          reader.releaseLock();
          break;
        }
        window.serialvalue = value;
      }
    } catch (error) {
      console.error(error);
    } finally {
      console.log("releasing...");
      reader.releaseLock();
    }
  }
};
doserial();
