var express     = require('express')
   ,app         = express()
   ,http        = require('http').Server(app)
   ,io          = require('socket.io')(http)
   ,port        = process.env.PORT || 3001
   ,zmq         = require('zeromq')
   ,requester   = zmq.socket('req')
   ,cv          = require('opencv4nodejs');

require('events').EventEmitter.prototype._maxListeners = 100;

app.use(express.static('public'))

app.get('/', function(req, res){
    res.sendFile(__dirname + '/public/index.html');
});

io.on('connection', (socket) => {
    requester.on('message', data => {
        // var mat = cv.imread('MinaTWICE.jpg')
        var mat = new cv.Mat(data, 480, 640, cv.CV_8UC3)
        var base =  cv.imencode('.jpg', mat).toString('base64')
        socket.emit('frame', base)
    });
})

requester.connect("tcp://localhost:5555");

setInterval(function() {
    requester.send("Hello");
}, 100)

http.listen(port, function(){
    console.log('listening on *:' + port);
});