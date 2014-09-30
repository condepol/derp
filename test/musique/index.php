<?php
$dirname = dirname($_SERVER['PHP_SELF']);
$folder_name = basename($dirname);
$subindex = ".subindex";

// 1. Check subfolders index presence, create it when needed.
if ((file_exists($subindex) === False) or ($_GET['refresh'] == 1)) {
  exec("find . -type f -name \*.ogg | sort > {$subindex}");
}

// 2. Parse subfolders index
$subfiles = file ( $subindex, FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);

?>
<!doctype html>
<html>
  <head>
    <meta charset=utf8 />
    <title><?php echo "{$dirname}";?></title>
<link href="/musique/skin/pink.flag/jplayer.pink.flag.css" rel="stylesheet" type="text/css" />
<link href="/musique/skin/musique.css" rel="stylesheet" type="text/css" />
<script type="text/javascript" src="/musique/js/jquery-1.11.0.min.js"></script>
<script type="text/javascript" src="/musique/js/jquery.jplayer.min.js"></script>
<script type="text/javascript" src="/musique/js/jplayer.playlist.min.js"></script>
<script type="text/javascript">
//<![CDATA[
$(document).ready(function(){

  new jPlayerPlaylist({
    jPlayer: "#jquery_jplayer_1",
    cssSelectorAncestor: "#jp_container_1"
  }, [
    <?php foreach (range(0,sizeof($subfiles)) as $index) {
      $oga = $subfiles[$index];
      $title = basename($oga);
      $artist = basename(dirname($oga));
      if ($artist == ".") {
        $artist = basename($dirname);
      }
    ?>
    {
      title:"<?php echo "{$title}";?>",
      oga:"<?php echo "{$oga}";?>",
      artist:"<?php echo "{$artist}";?>",
      free:"true",
    },
    <?php } ?>
    ], {
    swfPath: "/musique/js",
    supplied: "oga",
    wmode: "window",
    smoothPlayBar: true,
    keyEnabled: true
  });
});
//]]>
</script>
<?php 
if (isset($_GET['autoplay']) and preg_match('/[0-9]*/',$_GET['autoplay'])) {
?>
<script type="text/javascript">
document.addEventListener('DOMContentLoaded', function() {
    setTimeout(function () {
      document.getElementById("le_wild_playlist")
              .getElementsByTagName("li")[<?php echo "{$_GET['autoplay']}";?>]
              .getElementsByTagName("a")[2].click();
    },300);
});
</script>
<?php } ?>
  </head>
  <body>
    <a href="<?php $root=dirname($dirname);echo "{$root}"; ?>" class="parent">↸ <?php if ($root==="/") { echo "racine";} else {echo "{$root}";} ?></a><br />
    <?php 
    $tmp = "n¬";
    foreach (range(0,sizeof($subfiles)) as $index) {
      $folder = dirname($subfiles[$index]);
      $artist = basename($folder);
      if (($folder !== $tmp) and ($folder !== "." )) {
        ?>
        <a href="<?php echo "{$folder}"; ?>"><?php echo "{$folder}"; ?></a><br />
        <?php
        $tmp = $folder;
      }
    }
    ?>
		<div id="jquery_jplayer_1" class="jp-jplayer"></div>

		<div id="jp_container_1" class="jp-audio">
			<div class="jp-type-playlist">
				<div class="jp-gui jp-interface">
					<ul class="jp-controls">
						<li><a href="javascript:;" class="jp-previous" tabindex="1">previous</a></li>
						<li><a href="javascript:;" class="jp-play" tabindex="1">play</a></li>
						<li><a href="javascript:;" class="jp-pause" tabindex="1">pause</a></li>
						<li><a href="javascript:;" class="jp-next" tabindex="1">next</a></li>
						<li><a href="javascript:;" class="jp-stop" tabindex="1">stop</a></li>
						<li><a href="javascript:;" class="jp-mute" tabindex="1" title="mute">mute</a></li>
						<li><a href="javascript:;" class="jp-unmute" tabindex="1" title="unmute">unmute</a></li>
						<li><a href="javascript:;" class="jp-volume-max" tabindex="1" title="max volume">max volume</a></li>
					</ul>
					<div class="jp-progress">
						<div class="jp-seek-bar">
							<div class="jp-play-bar"></div>

						</div>
					</div>
					<div class="jp-volume-bar">
						<div class="jp-volume-bar-value"></div>
					</div>
					<div class="jp-current-time"></div>
					<div class="jp-duration"></div>
					<ul class="jp-toggles">
						<li><a href="javascript:;" class="jp-shuffle" tabindex="1" title="shuffle">shuffle</a></li>
						<li><a href="javascript:;" class="jp-shuffle-off" tabindex="1" title="shuffle off">shuffle off</a></li>
						<li><a href="javascript:;" class="jp-repeat" tabindex="1" title="repeat">repeat</a></li>
						<li><a href="javascript:;" class="jp-repeat-off" tabindex="1" title="repeat off">repeat off</a></li>
					</ul>
				</div>
				<div class="jp-playlist" id="le_wild_playlist">
					<ul>
						<li></li>
					</ul>
				</div>
				<div class="jp-no-solution">
					<span>Update Required</span>
					To play the media you will need to either update your browser to a recent version or update your <a href="http://get.adobe.com/flashplayer/" target="_blank">Flash plugin</a>.
				</div>
			</div>
		</div>
  </body>
</html>
