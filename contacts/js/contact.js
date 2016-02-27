function getContactRow(contactObj) {
    var result = "<tr>";
    result = result + "<td><img src=\"" + contactObj.imguri + "\" class=\"img-circle alt=\"CinqueTerre\" width=\"35\" height=\"35\"/></td>";
    result = result + "<td>" + contactObj.name + "</td>";
    result = result + "<td>" + contactObj.tel + "</td>";
    result = result + "<td>" + contactObj.email + "</td>";
    result = result + "<td><button class=\"buttonstyle\">delete</button></td>";
    result = result + "<td><button class=\"buttonstyle\">update</button></td>";
    result = result + "</tr>";
    
    return result;
}

function clearContactList() {
    $("#contacts_table tbody").empty();
}

function insertContactToList(htmlStr) {
    $("#contacts_table tbody").append(htmlStr);
} 

function refreshContactList() {
    $.get("php/query_contacts.php", {}, function (data) { 
        var obj = jQuery.parseJSON(data);
        var contacts_array = obj.contacts;

        clearContactList();
        for(var num = 0; num < contacts_array.length; num++) {
            insertContactToList(getContactRow(contacts_array[num]));
        }
    });
}

function refreshContactListAjax() {
    var url_ = "php/query_contacts.php";
    $.ajax({
	type: "GET",
	url: url_,
	dataType: "json",
	success: function(data) {
            var obj = data;
            var contacts_array = obj.contacts;

            clearContactList();
            for(var num = 0; num < contacts_array.length; num++) {
		insertContactToList(getContactRow(contacts_array[num]));
            }
	},
	error: function() {
	    alert("Error: fetch contacts list failed.");
	}
    });
}

$(document).ready(function() {
    refreshContactListAjax();
    
    $("#button_refresh").click(function() {
        refreshContactListAjax();
    });
    
    $("#button_insert_contact").click(function() {
        var url_ = "php/insert_contact.php";    
        $.ajax({
            type: "POST",
            url: url_,
            data: $("#form_insert_contact").serialize(), // serializes the form's elements.
            dataType: "json",
            success: function(data) {
                refreshContactListAjax();
            },
            error: function() {
                alert("error insert");
            }
        });
        return false; // avoid to execute the actual submit of the form.
    });
    
});

