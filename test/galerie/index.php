<!doctype html>
<html>
  <head>
    <meta charset=utf8 />
    <title><?php $dirname = dirname($_SERVER['PHP_SELF']); echo basename($dirname);?></title>
    <script>
    var images = [<?php
    $images = [];
    if ($handle = opendir('.')) {
      while (false !== ($entry = readdir($handle))) {
        if (preg_match('/^.*\.(jpe?g|png|gif)$/i', $entry)) {
          array_push($images,$entry);
        }
      }
      closedir($handle);
    }
    // sort by date
    usort($images, function($a, $b) {
          return filemtime($a) < filemtime($b);
    });
    foreach ($images as $image) { echo "'{$image}',";}

?>
    ];
    var index = 0;
    function refresh () {
      if (index < 0) {
        index = 0;
      } else {
        if (index > images.length) {
          index = images.length - 1;
        }
      }
      document.getElementById("the_image").src = "<?php echo $dirname; ?>/" + images[index];
      document.getElementById("the_image").alt = images[index];
      document.getElementById("index").innerHTML = index + " / " + images.length;
      document.getElementById("filename").innerHTML = images[index];
      document.getElementById("progress").style.width = Math.floor(100 - (100 * index / images.length)) + "px";
    }
    </script>
    <style>
      html {margin: 0px 0px 0px 0px;padding: 0px 0px 0px 0px;}
      body {margin: 0px 0px 0px 0px;padding: 0px 0px 0px 0px;}
      div {margin: 0px 0px 0px 0px;padding: 0px 0px 0px 0px;}
      img {margin: 0px 0px 0px 0px;padding: 0px 0px 0px 0px; height: 100%;}
      .window {width: 100%; height: 100%; float:left; margin: 0px 0px 0px 0px}
      .left   {width: 50px; height: 50px; background: #faa; position:absolute; top: 0px; right: 50px; text-align: center;font-size: 2em;}
      .right  {width: 50px; height: 50px; background: #afa; position:absolute; top: 0px; right:  0px; text-align: center;font-size: 2em;}
      .filename {background: #ddd; opacity: 0.8; position: absolute; top: 70px; right: 0px;}
      .index    {background: #ddd;; position: absolute; top: 50px; right: 0px;   height: 20px;font-size: 15px; width : 100px; text-align: center;}
      .progress-bg  {background: #f88; position: absolute; top: 67px; right: 0px; height: 3px; width: 100px;}
      .progress     {background: #8f8; position: absolute; top: 67px; right: 0px; height: 3px;}
    </style>
  </head>
  <body>
    <div id="viewer">
      <div id="window"  class="window">
        <img id="the_image" src="" alt="" />
      </div>
      <div id="left"    class="left">←</div>
      <div id="right"   class="right">→</div>
      <div id="index"     class="index" ></div>
      <div                class="progress-bg" ></div>
      <div id="progress"  class="progress" ></div>
      <div id="filename"  class="filename" ></div>
    </div>
    <script>
    document.addEventListener('DOMContentLoaded',function () {
        document.getElementById("left") .addEventListener('click',function () {index -= 1; refresh();});
        document.getElementById("right").addEventListener('click',function () {index += 1; refresh();});
        document.onkeydown = function(e) {
              e = e || window.event;
                  switch(e.which || e.keyCode) {
          case 37: index -= 1; refresh(); break;
          case 39: index += 1; refresh(); break;
          default: return; // exit this handler for other keys
        }
        e.preventDefault(); // prevent the default action (scroll / move caret)
      };
      refresh();
    });
    </script>
  </body>
</html>
