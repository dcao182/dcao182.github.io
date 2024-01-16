import React from "react";
import { Link } from "react-router-dom";

function Card_HomePage({
  imageUrl,
  image_alt,
  title,
  description,
  btnContent,
  link_url,
}) {
  return (
    <div className="card w-96 bg-base-100 shadow-xl mx-6">
      <figure>
        <img src={imageUrl} alt={image_alt} />
      </figure>
      <div className="card-body">
        <h2 className="card-title">{title}</h2>
        <p>{description}</p>
        <Link to={link_url}>
          <div className="card-actions justify-end">
            <button className="btn btn-primary">{btnContent}</button>
          </div>
        </Link>
      </div>
    </div>
  );
}

export default Card_HomePage;
