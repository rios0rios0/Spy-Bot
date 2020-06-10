var timer;
var istrue = false;
var delay = 300; // how much long u have to hold click in MS
function func(e)
{
   istrue = true;
   timer = setTimeout(function(){ makeChange();},delay);
  // Incase if you want to prevent Default functionality on mouse down
  if (e.preventDefault) 
  { 
     e.preventDefault();
  } else {
     e.returnValue = false; 
  }
}

function makeChange()
{
      if(timer)
      clearTimeout(timer);

      if(istrue)
      {
            /// rest of your code
          ///document.getElementById("go").click();
		  ///document.myForm.mySubmit.click();
		  alert('holding');
		  

      }
}
function revert()
{
   istrue =false;
}
function whateverFunc()
{
    alert('dblclick');
}
