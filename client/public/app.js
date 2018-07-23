var socket = io()

var canvas = document.getElementById('canvas-video');
var context = canvas.getContext('2d');
var img = new Image();

context.fillStyle = '#333';
context.fillText('Loading...', canvas.width/2-30, canvas.height/3);

socket.on('frame', function (datas) {
    img.src = 'data:image/jpeg;charset=utf-8;base64,' + datas;
    img.onload = () => {
      context.drawImage(img, 0, 0, canvas.width, canvas.height);
    }
})