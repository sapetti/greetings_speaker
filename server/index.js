
const kill  = require('tree-kill');
const express = require('express');
const app = express();
const player = require('play-sound')(opts = {});
const port = 3000;
const file = 'file.mp3';
var running = false;

function playSong() {
  running = true;
  const options = {
    omxplayer: ['--pos', '00:00:27'],
  };
  const process = player.play(file, options, handleError);
  setTimeout(() => kill(process.pid), 3500);
  setTimeout(() => running = false, 30000);
}

app.get('/play-sound', (req, res) => {
  res.send('Done!');
  if(!running) playSong();
});

function handleError(error) {
  if(error) console.log(error);
}

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
});