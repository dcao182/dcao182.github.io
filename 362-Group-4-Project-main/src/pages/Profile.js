import { useEffect } from "react";
import { useAuth } from "../contexts/AuthContext.js";
import { Link } from "react-router-dom";

function Profile() {
  const { currentUser } = useAuth();
  console.log(currentUser.uid);
  useEffect(() => {});
  return currentUser ? (
    <>
      <div>{currentUser.email}</div>
      <button className="btn btn-primary">
        <Link to={"/create-listing"}>Create Listing</Link>
      </button>
    </>
  ) : (
    <h1>Not Logged In</h1>
  );
}

export default Profile;
